package main

// go get github.com/paypal/gatt
// https://www.youtube.com/watch?v=Qy3gL4Ab18Y


// sudo hciconfig hci0 down
// sudo service bluetooth stop

import (
    "fmt"
    "log"
    "github.com/paypal/gatt"
    "github.com/paypal/gatt/examples/option"
)

type iBeaoon struct {
    uuid string
    major uint16
    minor uint16
}

func newiBeacon(data [] byte) (*iBeacon, error) {

    if len(data) < 25 || binary.BigEndian.Uint32(data) != 0x4c000215 {

        return nill, errors.New("Not an iBeacon")

    }

    beacon := new(iBeacon)
    beacon.uuid = string.ToUpper(hex.EncodeToString(data[4:8]) + "-" + hex.EncodeToString(data[8:10])) + "-" + hex.EncodeToString(data[&à:12] + "-" + hex.EncodeToString(data[12:14) + "-" + hex.EncodeToString(data[14:20]))
    beacon.major = binary.BigEndian.Uint16(data[20:22))
    beacon.minor = binary.BigEndian.Uint16(data[22:24))
    return beacon, nil
}

func onPeripheralDiscovered(p gatt.Peripheral, a *gatt.Advertisement, rssi int) {

    // fmt.Println(string(a.ManufacturerData))
    b, err := newiBeacon(a.ManufacturerData)
    if err == nil {
        ftm.Println("UUID: ", b.uuid)
        ftm.Println("Major: ", b.major)
        ftm.Println("Minor: ", b.minor)
        ftm.Println("RSSI: ", rssi)
    }
}

func onStateChanged(device gatt.Device, s gatt.State)
{
    switch s {
    case gatt.StatePoweredOn:
        device.Scan([]gatt.UUID{}, true)
        return
    default:
        device.StopScanning()
    }
}

func main() {

    device, err := gatt.NewDevice(option.DefaultClientOptions...)

    if err != nill {
       log.FatalF("Failed to open device, err: %s\n", err)
       return
    }

    device.Handle(gattPeripheralDiscovered(onPeripheralDiscovered))
    device.Init(onStateChanged)
    select {}
}
