# SleepWake Example

This example demonstrates how to use the sleep capabilities of the Padauk controller.

It will blink an LED 3 times then go to sleep. When the switch pin sees any level change,
it will wake up, blink the LED 3 more times, then go back to sleep.

### Hardware Circuit

By default the LED is on PA4. This example leaves the LED pin HIGH while asleep, so to ensure
power consumption is low the microntroller should be connected to the negative lead of the LED.

By default PA0 is used as the wakeup pin. Any level change will trigger a wakeup.

### Notes

It seems that at higher voltages the current draw may be higher even in sleep mode.
This appnote suggests there's internal leakage between PA5 and GND.

https://www.padauk.com.tw/upload/ApplicationNote/APN012_PMS150B_Power_Saving_Mode_v001_EN.pdf

The datasheet suggests STOPSYS will consume about 0.5uA, but with VCC=5v I measured 13uA.
Powering the chip from 3.3v however, I measured 0.2uA (but my multimeter may not be that accurate).

### Toolchain:
- The open-source [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/)
  - Requires version 3.9.0 or newer - version 4.0.0+ preferred
- The open-source [Easy PDK Programmer](https://github.com/free-pdk/easy-pdk-programmer-software)
  - Requires version 1.3 or newer
- The open-source [pdk-includes](https://github.com/free-pdk/pdk-includes) repository
  - Integrated via local copy into the include/ directory
- The open-source [easy-pdk-includes](https://github.com/free-pdk/easy-pdk-includes) repository
  - Integrated via local copy into the include/ directory
- Also requires 'make' and other common build tools

### Build Commands:
```
make clean
make build
make size (also calls build)
make program (also calls size which calls build)
make run
```
> Note: These commands can be chained as well.  i.e. `make clean program run`


### Customization:
Edit the variables at the top of the Makefile to:
- **DEVICE**: Use a different Padauk MCU (defaults to PFS154)
- **F_CPU**: Use a different frequency for the system clock (defaults to 1MHz, i.e. IHRC/16)
  > Note: The `AUTO_INIT_SYSCLOCK()` macro in the `STARTUP_FUNCTION()` method will automatically choose the correct internal oscillator (IHRC or ILRC) and clock divider based on the desired frequency.
  > The `AUTO_CALIBRATE_SYSCLOCK(vdd)` macro will install a placeholder for the correct internal oscillator (IHRC or ILRC) that the Easy PDK Programmer will use to calibrate to the desired frequency.
- **TARGET_VDD_MV**: Use a different voltage while calibrating the internal oscillator (IHRC or ILRC) (defaults to 4000mV)
- **TARGET_VDD**: Use a different voltage while the IC is operating (defaults to 4.0V)

> Note: All of these variables can be changed on the commandline as well.  i.e. `make DEVICE=PFS173 clean program run` 

### Compatibility
This example should run on every currently known Padauk microcontroller that is supported by SDCC and the Easy PDK Programmer.
A device specific include file (pdk/device/*.h) may need to be supplied for less common devices.

### Build Stats
- Code Size: 100 words (200 bytes)
