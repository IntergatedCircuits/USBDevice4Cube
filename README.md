# STM32Cube wrapper of [USBDevice][USBDevice]

This is a simple example project stub which serves as a starting point to integrate the [USBDevice][USBDevice] library
into an STM32CubeMX project. Since all STM32 devices have the same USB or USB_OTG peripherals, this solution is compatible
throughout the entire STM32 range (but don't be afraid to report an issue if this turns out not to be so).

## How to use
1. The `XPD_USB` folder has to be added to the project as-is. It contains both source and header files.
2. The `Inc/stm32xxxx.h` file simply has to include the series-specific CMSIS and HAL headers.
3. The `Src/hal_usb.c` should contain the dependency (GPIO pins and NVIC interrupts) configuration e.g. copied from `usbd_conf.c`.
The interrupt handler redirection can be done either here, or in the project-specific `stm32xxxx_it.c`.
4. Use the `Src/main.c` and `Src/usb_device.c` as starting point to implement your own USB device application.
5. Open an issue if something is unclear or if the integration is unsuccessful.

## Application notes

### External DP pull-up
* The USB peripheral of F1, F3 and L1 series doesn't have built-in pull-up 1.5 kOhm resistor between the USB DP line and VDD.
Therefore such resistor must be supplied externally onboard. In order to support soft-detach of the device,
it is recommended to place this resistor between DP and a GPIO output. In software a simple method must be implemented,
which sets the GPIO pin's output state to the input parameter value. This function's pointer must be passed
to the USB device handle during init:

`UsbDevice->Callbacks.ConnectCtrl = usbAttachDetach;`

[USBDevice]: https://github.com/IntergatedCircuits/USBDevice
