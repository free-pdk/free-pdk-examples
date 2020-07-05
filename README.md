# free-pdk-examples
Code Examples for Padauk MCUs using the free-pdk toolchain

### Examples:
- [BlinkLED](BlinkLED) - Turns an LED on for one second, then off for one second, repeatedly.
- [FadeLED](FadeLED) - Uses PWM to fade an LED in and out, repeatedly.
- [ReadButton_WriteLED](ReadButton_WriteLED) - Reads a Button (digital input) and turns on an LED when active.
- [Serial_HelloWorld](Serial_HelloWorld) - Transmits "Hello World" @ ~115200 baud, and repeats once a second.
- [ReadButton_WriteSerial](ReadButton_WriteSerial) - Reads a Button (digital input) and transmits the results over Serial @ ~115200 baud.

### Toolchain:
- SDCC Compiler: [SDCC](http://sdcc.sourceforge.net/) (3.9.0 or newer - 4.0.0+ preferred)
- Easy PDK Programmer: [easy-pdk-programmer-software](https://github.com/free-pdk/easy-pdk-programmer-software) (v1.3 or newer. Currently in development branch)
- PDK device includes: [pdk-includes](https://github.com/free-pdk/pdk-includes)
  - Integrated as git Submodule
- Easy PDK Programmer includes: [easy-pdk-includes](https://github.com/free-pdk/easy-pdk-includes)
  - Integrated as git Submodule
- Also requires 'make' and other common build tools
