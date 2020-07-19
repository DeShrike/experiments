
# (C) 2019 Simon Funk simon@sifter.org
# You're free to use this for non-commercial purposes.

import struct
from time import time, sleep

from bluepy.btle import UUID, Peripheral, Characteristic, Scanner, Service, DefaultDelegate, BTLEGattError

debug = False

#
# If True, this makes sure we don't initiate any two transactions too close
#  together. But in practice it may be more important not to initiate too soon
#  after the *end* of the previous, which we can do dumbly by just adding a delay
#  before all actions (which is what happens if we leave this False).
#
smart_throttle = False

def set_debug(level):
    global debug
    if level != debug:
        import bluepy.btle
        debug = level
        bluepy.btle.Debugging = level

class BtleDevice(DefaultDelegate):

    """Base class for a connection to a Bluetooth Low Energy device.

    Built on bluepy (which is built on bluez), and uses some bluepy classes,
    so this class is just a helper not really a full API.

    See https://ianharvey.github.io/bluepy-doc/index.html

    **** NOTE *****
    As of 2019-12-06, you have to fix a bug in the btle.py library:
    Comment out the _getResp in disconnect() or it can hang on readline
        when a 'stat disc' reply from the helper is overlooked (as in
        during a call to setMTU).
    **** NOTE *****
    """
    # Common Services:
    generic_access_service_uuid     = UUID('1800')
    device_info_service_uuid        = UUID('180a')

    # Common Descriptors:
    characteristic_description_uuid = UUID('2901')
    characteristic_configure_uuid   = UUID('2902')

    # Common Characteristics:
    model_number_uuid      = UUID('2a24')   # As string
    serial_number_uuid     = UUID('2a25')   # As string
    firmware_revision_uuid = UUID('2a26')   # As string
    hardware_revision_uuid = UUID('2a27')   # As string
    manufacturer_name_uuid = UUID('2a29')   # As string

    def __init__(self, mac_addy, mtu=0xff, max_rate=10):
        """Connect to the device at the specified addy.

        Max_rate is the maximum rate in messages/second at which we will
            send messages to the device.  I imagine this could/should be
            automatically inferred from the Peripheral Preferred Connection
            Parameters, but that's above my pay grade.  All I know is,
            if you don't meter the outgoing messages, some peripherals
            will just start dropping requests, resulting in timeouts
            waiting for the acks.  For an Airthings Wave+, max_rate 10
            works with dumb throttling, or max_rate 5 with smart.  The
            whole issue seems fishy to me -- seems like the lower level
            protocols should handle this better.  But pragmatically, it
            regularly hangs without this.
        """
        DefaultDelegate.__init__(self)
        assert mac_addy

        self.mac_addy   = mac_addy
        self.mtu        = mtu
        self.min_delay  = 1./max_rate
        self.peripheral = None

        self.cache             = None   # Will be dict mapping UUIDs to Characteristics; Created/cleared by connect()
        self.last_notification = None   # This is only used transiently by the default notification handler.  Ignore!

        if smart_throttle:
            self.last_xmt_time = 0      # Used to throttle outgoing messages.  Is the time() of last sent message (or 0)

    #=====
    # If you don't know the MAC address, you'll need to scan, but that requires root...
    #=====

    @staticmethod
    def scan(match=None, duration=5, just_one=False, match_scan_entry=False):
        """This looks through any advertising btle devices for matching ones.

        *** Note you must run this as root ***

        match(scan_data) should return True if scan_data is from the device you're looking for.

            If no match function is provided, it is treated as always returning True (you want
                to see all devices that respond within duration).

            scan_data is a dict mapping description to value, unless match_scan_entry is True
                in which case scan_data is a btle ScanEntry object.

        Duration is how many seconds to scan before returning.

        If just_one is False, scans for the full duration and then
            returns a list of matching ScanEntry objects. (https://ianharvey.github.io/bluepy-doc/scanentry.html)

        If just_one is True, this returns the first match immediately (no list)
            or None after full duration timeout.

        Note (match==None and just_one==True) results in just the first device
            to respond being immediately returned.
        """
        scanner = Scanner().withDelegate(DefaultDelegate())
        scanner.clear()
        scanner.start()
        if not just_one:
            found = []
        try:
            for i in range(max(int(duration*10),1)):    # Break duration into 10ths
                scanner.process(0.1)                    # Handle incoming messages for 1/10th of a second...
                devices = scanner.getDevices()
                for dev in devices:
                    if debug:
                        BtleDevice.dump_scan_entry(dev)
                    if match_scan_entry:
                        params = dev
                    else:
                        params = {name:val for tag, name, val in dev.getScanData()}
                    if match is None or match(params):
                        if just_one:
                            return dev
                        else:
                            found.append(dev)
                scanner.clear()
        finally:
            scanner.stop()

        if just_one:
            return None
        return found

    def disconnect(self):
        """Do call this when you are done!
        (But no sooner.  This will automatically re-connect if you try to do anything after this...)
        """
        if self.peripheral is not None:
            if debug:
                print("Disconnecting.") # TODO - need to wrap all these debugging messages in a better logger...
            self.throttle()
            self.peripheral.disconnect()
            self.peripheral = None
            self.cache      = None
            return True
        return False

    def connect(self):
        """Optional: Connects to the device.

        Returns True if this causes the connection, or False if we were already connected.

        Most of the methods here will call this on-demand, so you only need to call this
            explicitly if you want to access self.peripheral directly straight away.
        """
        if self.peripheral is None:
            if debug:
                print("Connecting to %s."%(self.mac_addy,))
            self.cache      = {}
            self.peripheral = Peripheral(self.mac_addy).withDelegate(self)
            if self.mtu is not None:
                self.throttle()
                self.peripheral.setMTU(self.mtu)    # Notification and Indications may not happen if we don't do this.
            return True
        return False

    #=====
    # Most of the good stuff is here -- ways to read and write values:
    #=====

    def __getitem__(self, char):
        """This reads and returns the current value of the given characteristic.
        Char can be a uuid string, UUID object, or Characteristic object.
        """
        self.throttle()
        return self.get_characteristic(char).read()

    def __setitem__(self, char, val):
        """This writes the byte array val to the specified characteristic.
        Char can be a uuid string, UUID object, or Characteristic object.
        """
        self.throttle()
        self.get_characteristic(char).write(val, True)

    def get_handle(self, char):
        """This returns the Handle (small integer) of the specified characteristic.
        Char can be a uuid string, UUID object, or Characteristic object.
        Mainly useful to compare to the handle returned by wait_for_notification().
        """
        return self.get_characteristic(char).getHandle()

    def get_characteristic(self, uuid):
        """If you're just doing basic sets, queries and commands with the high
            level interface you probably don't need to call this directly.

        This accepts strings or UUID objects and returns the associated
            Characteristic object.  (Or the first one if there are multiple
            with the same UUID.  So, this is mainly useful for high level
            variables, not for meta information attributes or such.)
        As a convenience, if you pass a Characteristic, this will return it.
            (Which is useful for functions that want to allow flexible
            identification of the Characteristic.)
        Results are cached for efficiency, so don't be shy about using it.
        Raises KeyError if uuid can't be found.
        """
        self.connect()
        if isinstance(uuid, Characteristic):
            return uuid
        if not isinstance(uuid, UUID):
            uuid = UUID(uuid)
        if uuid not in self.cache:
            self.throttle()
            c = self.peripheral.getCharacteristics(uuid=uuid)
            if c:
                self.cache[uuid] = c[0]
            else:
                self.cache[uuid] = None
        c = self.cache[uuid]
        if c is None:
            raise KeyError("Can't find characteristic %s"%(uuid,))
        return c

    #=====
    # If you want Notifications or Indications, you need to enable each characteristic accordingly.
    #=====

    def can_notify(self, char):
        """Returns non-zero if this characteristic can generate Notifications or Indications.

        Char can be a uuid string, UUID object, or Characteristic object.

        Technically the return value can be further inspected to discern whether it
            supports Notifications, Indications, or (does this ever happen?) both.
        """
        char = self.get_characteristic(char)
        return char.properties & (char.props['INDICATE']|char.props['NOTIFY'])

    def enable(self, char):
        """Usually this is the easiest way to enable notifications from a characteristic.

        You have to call this (or one of the more specific ones below) before you will
            get any notifications from a given Characteristic.

        This enables characteristic char for either Indications or Notifications depending
            on which sort it claims to generate.

        Char can be a uuid string, UUID object, or Characteristic object.
        """
        char = self.get_characteristic(char)
        if char.properties & char.props['INDICATE']:
            self.configure_characteristic(char, 2)
        elif char.properties & char.props['NOTIFY']:
            self.configure_characteristic(char, 1)
        else:
            raise Exception("Characteristic does not support any notifications: %s"%(char,))

    def disable(self, char):
        self.configure_characteristic(char, 0)

    def wait_for_notification(self, timeout):
        """This waits for the next notification and then returns it
            as a (handle, data) tuple.

        This only works if you do not override handleNotifications.

        This only handles notifications that come in during this call.
            If you call this successively, you should catch all notifications
            as long as you don't make any other Btle calls in between (since
            those calls could let a notification slip into the gap).

        Returns None on timeout.
        """
        try:
            self.last_notification = False      # False means we're waiting; None means we're not!
            if self.peripheral.waitForNotifications(timeout):
                return self.last_notification   # Python should grab it before the finally clause resets it...
            else:
                return (None, None)
        finally:
            self.last_notification = None       # Make sure handleNotifications alerts us to notifications that come out of band.

    def handleNotification(self, handle, data):
        """Subclass can override this to do whatever it wants with notifications/indications.
        """
        if self.last_notification is None:
            # Don't put this under Debug flag.  This alerts you to Notifications you aren't handling yet...
            print("UNHANDLED NOTIFICATION: handle=%r data=%r"%(handle, data.hex()))
        else:
            self.last_notification = (handle, data)

    #--- Unlikely you need to call any of these directly:

    def enable_notifications(self, char):
        """If you want to get Notifications from a characteristic, you need to call this first.
        Char can be a uuid string, UUID object, or Characteristic object.
        Note this also disables Indications for this characteristic.  Use configure_characteristic to enable both.
        """
        self.configure_characteristic(char, 1)

    def enable_indications(self, char):
        """If you want to get value Indications from a characteristic, you need to call this first.
        Char can be a uuid string, UUID object, or Characteristic object.
        Note this also disables Notifications for this characteristic.  Use configure_characteristic to enable both.
        """
        self.configure_characteristic(char, 2)

    def configure_characteristic(self, char, val):
        """This looks up the handle for the configuration descriptor for this characteristic,
            and then sends val to it.
        Char can be a uuid string, UUID object, or Characteristic object.
        Typically val here is 1 (enable Notifications) or 2 (enable Indications) or 0 (disable).
        """
        char = self.get_characteristic(char)
        if debug:
            print("Finding configuration descriptor for handle 0x%x"%(char.getHandle(),))
        self.throttle()
        d, = char.getDescriptors(forUUID=self.characteristic_configure_uuid)
        if debug:
            print("Found (handle 0x%x).  Setting to 0x%02x"%(d.handle, val))
        self.throttle()
        d.write(struct.pack('<H', val), True)

    def throttle(self):
        """This internal utility just waits until self.min_delay from the
            last time this method was called.
        """
        if smart_throttle:
            now   = time()
            delay = self.last_xmt_time + self.min_delay - now
            if delay > 0:
                sleep(delay)
                now += delay
            self.last_xmt_time = now
        else:
            sleep(self.min_delay)

    #=====
    # Below here are just utilities for displaying the device's data layout,
    # Which also serve as examples of how to access the devices's attributes.
    #=====

    def dump_services(self, read=False, indent=''):
        """This calls dump_service on all services this device provides.
        If read is True, it reads and prints each characteristic's value.

        This is a good way to manually discover the layout of your device.
        """
        self.connect()
        for s in self.peripheral.getServices():
            self.dump_service(s, read, indent)

    def dump_service(self, service, read=False, indent=''):
        """This calls dump_characteristic on all the characteristics in the given service.
        If service is not a Service object, it's assumed to be a UUID and the service
            will be looked up by that.
        """
        self.connect()

        if not isinstance(service, Service):
            try:
                service = self.peripheral.getServiceByUUID(service)
            except BTLEEException:
                print("%sService %r: NOT FOUND"%(indent,service))
                return

        print("%sService %r (%s):"%(indent, service.uuid.getCommonName(), service.uuid))
        for c in service.getCharacteristics():
            self.dump_characteristic(c, read, indent+"    ")

    def dump_characteristic(self, c, read=False, indent=''):
        """Dumps whatever we can find out about a characteristic.
        If read is True, also reads and prints its value (when applicable)
        """
        print("%sCharacteristic %r (%s):"%(indent, c.uuid.getCommonName(),c.uuid))
        print("%s          Handle: %s (%x)"%(indent, c.getHandle(), c.getHandle()))
        print("%s        Readable: %s"%(indent, c.supportsRead(),))
        print("%s      Properties: %s"%(indent, c.propertiesToString(),))

        try:
            descriptors = c.getDescriptors()
        except BTLEGattError:
            pass
        else:
            for d in descriptors:
                print("%s      Descriptor: %s (handle 0x%x; uuid %s)"%(indent, d, d.handle, d.uuid))
                if d.uuid == self.characteristic_description_uuid:
                    self.throttle()
                    print("%s          ------> %r"%(indent, d.read()))

        if c.supportsRead():
            try:
                self.throttle()
                val = c.read()
            except:
                print("%s    (Read) Value: [READ FAILED]"%(indent,))
            else:
                print("%s    (Read) Value: %s (0x%s)"%(indent, val, val.hex()))

    @staticmethod
    def dump_scan_entry(se):
        """Just prints the info that comes back from a Scan response.
        """
        print("Scanned Device:")
        print("              MAC: %s"%(se.addr,))
        print("        Addr Type: %s"%(se.addrType,))
        print("  Signal Strength: %s dB"%(se.rssi,))
        print("      Connectable: %s"%(se.connectable,))
        print("     Update Count: %s"%(se.updateCount,))
        for t in se.getScanData():
            print("  %r"%(t,))


if __name__ == "__main__":

    testDevice = 'a9:cf:21:3c:b6:53'    # MAC addy of any cooperative btle device
    testDevice = "d3:cb:9c:01:af:14"    # My micro:bit

    if True: #False:

        # Example of just displaying all the devices the scanner finds (requires root):

        def match(se):
            BtleDevice.dump_scan_entry(se)

        BtleDevice.scan(match, match_scan_entry=True)

    elif True:

        # Example of fetching a property from a known device:

        dev = BtleDevice(testDevice)
        try:
            print("Manufacturer: %s"%(dev[BtleDevice.manufacturer_name_uuid].decode()))
        finally:
            dev.disconnect()
    else:

        # Example of displaying the characteristic hierarchy of a known device:

        dev = BtleDevice(testDevice)
        try:
            dev.dump_services(True)
        finally:
            dev.disconnect()


