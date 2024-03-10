# BlinkLED_WithIRQ Example

This example demonstrates how to blink an LED without using a timing loop delay, allowing the MCU to do other things while waiting to turn the LED on or off again.

This example also demonstrates one way to implement a `millis()` function (similar to what Arduino provides).
The source code for the `millis()` code can be found in the [millis.h](../include/millis.h) include file.

There are certainly leaner ways of using a timer to blink an LED than the `millis()` technique.
For example, eliminating or using smaller than the 32-bit variables, could reduce the code / RAM requirements potentially significantly.
Simply using 16-bit instead of 32-bit variables reduces the code from 169 -> 122 words, and the ram requirements from 21 -> 7 bytes, although it means the millis counter will roll-over about every minute instead of every 49 days.

See the [BlinkLED](../BlinkLED) example for a simpler timing loop based approach. 

> _**Inspiration**: This example was inspired by the public domain [BlinkWithoutDelay](https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay) example from Arduino._

### Hardware Circuit
By default, the LED is placed on the PA4 pin* (Port A, Bit 4) with a current sink configuration.

This means the negative leg (or cathode) of the LED is connected to the digital pin of the IC, and the positive leg (or anode) of the LED is connected through a current limiting resistor to VDD.
- When the digital pin is LOW, current will flow through the LED and it will light up.
- When the digital pin is HIGH, no current will flow and the LED will turn off.

>_*Note: Please consult the pinout for the specific microcontroller package used to identify the correct physical pin._

### Internal Peripherals Used:
- **16-bit timer (T16)**: Timer and timer interrupt used by `millis()` for timekeeping.  

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
- Code Size: 169 words (338 bytes)
- RAM usage: 21 bytes + stack
  - Most of the 21 bytes are used by the `millis()` routines and variables (defined in the [millis.h](../include/millis.h) include file),
   as well as the millis related comparison/math found in `main()`.  Using smaller data types, or more efficient techniques, would help out if running into resource limits.
