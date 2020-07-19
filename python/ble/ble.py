import bluetooth
# from bluetooth.ble import DiscoveryService

# simple inquiry example

nearby_devices = bluetooth.discover_devices(lookup_names=True)
print("Found {} devices.".format(len(nearby_devices)))

for addr, name in nearby_devices:
    print("  {} - {}".format(addr, name))

# bluetooth low energy scan

#service = DiscoveryService()
#devices = service.discover(2)

#for address, name in devices.items():
#    print("name: {}, address: {}".format(name, address))
