// SPIBus     Used to communicate with SPI devices
//
//  SPIBus(device)
//      Presents a set of functions for controlling SPI devices
//      on the specified device.
//
// Example: spi = SPIBus(vr);     // Creates an SPI bus on device 'vr'
function SPIBus(device) {

    // This allows an SPIBus to be created using 
    // y = new SPIBus() or y = SPIBus() syntax
    if (!(this instanceof SPIBus))
        return new SPIBus(device);

    if (arguments.length < 1)
        throw Error("SPIBus: Requires a device argument.");

    this.device = device;
}
