# ReadButton_WriteLED Example

This example demonstrates how to read the state of a Button connected to a digital input, and turns on an LED while the Button remains activated.

> _**Inspiration**: This example was inspired by the public domain [Button](https://www.arduino.cc/en/Tutorial/Button) example from Arduino._

### Hardware Circuit

**Button**:

By default, the Button is placed on Port A Bit 5 (PA5)* with an active low configuration.  The pin's internal pull-up resistor is utilized to avoid the need for an external resistor.
>_*Note: Please consult the pinout for the specific microcontroller package used to identify the correct physical pin._

This means that one side of the button is connected to the digital pin of the IC, and the other side is connected to GND.
- When the Button is idle, the internal pull-up resistor pulls the digital input towards VDD, and the pin is read as HIGH (1).
- When the Button is activated, it pulls the digital pin towards GND (overcoming the internal pull-up resistor), and the pin is read as LOW (0).

> _Note: The Easy PDK Programmer is not able to properly release the PA5 pin, so while the programmer is connected the pin will always be read as LOW.
To properly test this example, disconnect the programmer and use an external power source (or move the button to a different pin)._

**LED**:

By default, the LED is placed on Port A Bit 4 (PA4)* with a current sink configuration.
>_*Note: Please consult the pinout for the specific microcontroller package used to identify the correct physical pin._

This means the negative leg (or cathode) of the LED is connected to the digital pin of the IC, and the positive leg (or anode) of the LED is connected through a current limiting resistor to VDD.
- When the digital pin is LOW, current will flow through the LED and it will light up.
- When the digital pin is HIGH, no current will flow and the LED will turn off.

### Toolchain:
- Compiler: Requires [SDCC 3.9.0](http://sdcc.sourceforge.net/) (or newer, 4.0.0+ is recommended)
- Programmer: Requires [Easy PDK Programmer Hardware](https://github.com/free-pdk/easy-pdk-programmer-hardware) with [Easy PDK Programmer Software](https://github.com/free-pdk/easy-pdk-programmer-software)
  > **Important!** - In order for the clock calibration routines to function properly, the Easy PDK Programmer needs to be using re-compiled Firmware and easypdkprog software from the [development](https://github.com/free-pdk/easy-pdk-programmer-software/tree/development) branch.
**Both of these need to be re-compiled, and the Firmware needs to be re-programmed using dfu-util.**
Eventually, there will be a new release of easy-pdk-programmer-software (v1.3?) that will make this easier.
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
- **F_CPU**: Use a different frequency for the system clock (defaults to 1MHz = IHRC/16)
  > Note: The `AUTO_INIT_SYSCLOCK()` macro in the `_sdcc_external_startup()` method will automatically choose the correct internal oscillator (IHRC or ILRC) and clock divider based on the desired frequency.
  > The `AUTO_CALIBRATE_SYSCLOCK(vdd)` macro will install a placeholder for the correct internal oscillator (IHRC or ILRC) that the Easy PDK Programmer will use to calibrate to the desired frequency.
- **TARGET_VDD_MV**: Use a different voltage while calibrating the internal oscillator (IHRC or ILRC) (defaults to 4000mV)
- **TARGET_VDD**: Use a different voltage while the IC is operating (defaults to 4.0V)

> Note: All of these variables can be changed on the commandline as well.  i.e. `make DEVICE=PFS173 clean program run` 

### Compatibility
This example should run on every currently known Padauk microcontroller that is supported by SDCC and the Easy PDK Programmer.
A device specific include file (pdk/device/*.h) may need to be supplied for less common devices.

### Build Stats
- Code Size: 84 words (168 bytes)
- RAM usage: 7 bytes + stack
  - All 7 bytes are used as method call parameters for the timing loop routines defined in the [delay.h](../include/delay.h) include file.
