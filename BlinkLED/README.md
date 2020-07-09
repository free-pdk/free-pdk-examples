# Blink Example

This example shows just about the simplest thing you can do: it blinks an LED, on for one second, then off for one second, repeatedly.

Note: This example uses a timing loop to delay for one second.
See the [BlinkLED_WithIRQ](../BlinkLED_WithIRQ) example for a timer based approach. 

### Hardware Circuit
By default, the LED is placed on Port A, Pin 4 in a current sink configuration.

This means the negative leg (or cathode) of the LED is connected to the digital pin of the IC, and the positive leg (or anode) of the LED is connected through a current limiting resistor to VDD.
- When the digital pin is LOW, current will flow through the LED and it will light up.
- When the digital pin is HIGH, no current will flow and the LED will turn off.

##### Inspiration:
This example was inspired by the public domain [Blink](https://www.arduino.cc/en/Tutorial/Blink) example from Arduino.

### Toolchain:
- Compiler: Requires [SDCC 3.9.0](http://sdcc.sourceforge.net/) (or newer, 4.0.0+ is recommended)
- Programmer: Requires [Easy Pdk Programmer Hardware](https://github.com/free-pdk/easy-pdk-programmer-hardware) with [Easy Pdk Programmer Software](https://github.com/free-pdk/easy-pdk-programmer-software) (Need to use the 'development' branch for now)
- Also requires 'make' and other common build tools

### Build Commands:
```
make clean
make build
make size (also calls build)
make program (also calls size which calls build)
make run
```
Note: These commands can be chained as well.  i.e. `make clean program run`

### Customization:
Edit the variables at top of the Makefile to:
- **DEVICE**: Pick a different Padauk MCU (defaults to PFS154 if not changed)
- **F_CPU**: Use a different frequency for the system clock
  - Note: The _sdcc_external_startup() method will automatically choose the correct internal oscillator (IHRC or ILRC) and divider based on the desired frequency.
- **TARGET_VDD_MV**: Use a different voltage for internal oscillator (IHRC or ILRC) calibration
- **TARGET_VDD**: Use a different voltage while the IC is operating

Note: All of these variables can be changed on the commandline as well.  i.e. `make DEVICE=PFS173 clean program run` 

### Build Stats
- Code Size: 87 words (174 bytes)
- RAM usage: 7 bytes + stack
