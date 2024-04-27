# free-pdk-examples
Code Examples for Padauk MCUs using the free-pdk toolchain

### Warning: This is a work in progress and may change significantly before being considered stable.  Use at your own risk.

> _**Inspiration**: These examples were inspired by the [Arduino Built-In Examples](https://www.arduino.cc/en/Tutorial/BuiltInExamples) that have been placed into the public domain._

### Code Examples:
- [**BlinkLED**](BlinkLED) - Turns an LED on for one second, then off for one second, repeatedly.  Uses a timing loop for delays.
- [**BlinkLED_WithIRQ**](BlinkLED_WithIRQ) - Turns an LED on for one second, then off for one second, repeatedly.  Uses a timer interrupt for delays.
- [**FadeLED**](FadeLED) - Uses PWM to fade an LED in and out, repeatedly.
- [**ReadButton_WriteLED**](ReadButton_WriteLED) - Reads a Button (digital input), and turns on an LED when active.
- [**Serial_HelloWorld**](Serial_HelloWorld) - Transmits "Hello World" over Serial @ ~115200 baud, and repeats once a second.
- [**ReadButton_WriteSerial**](ReadButton_WriteSerial) - Reads a Button (digital input), and transmits the results over Serial @ ~115200 baud.
- **ReadAnalog_FadeLED** (TODO...) - Reads an analog input, and uses PWM to set the brightness of an LED.
- **ReadAnalog_WriteSerial** (TODO...) - Reads an analog input, and transmits the results over Serial @ ~115200 baud. 
- **ReadAnalog_WriteAverageSerial** (TODO...) - Reads an analog input, calculates a rolling average, and transmits the results over Serial @ ~115200 baud.
- **EchoSerial** (TODO...) - Echos back over Serial every line that is received.
- **ReadSerial_FadeLED** (TODO...) - Reads a value over Serial, and uses PWM to set the brightness of an LED.

### Toolchain:
- The open-source [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/)
  - Requires version 3.9.0 or newer - version 4.0.0+ preferred
  - **Some of the examples don't work with the neweset version of SDCC (4.4.0). Revert to SDCC 4.1.0 please**
- The open-source [Easy PDK Programmer](https://github.com/free-pdk/easy-pdk-programmer-software)
  - Requires version 1.3 or newer
- The open-source [pdk-includes](https://github.com/free-pdk/pdk-includes) repository
  - Integrated via local copy into the include/ directory
- The open-source [easy-pdk-includes](https://github.com/free-pdk/easy-pdk-includes) repository
  - Integrated via local copy into the include/ directory
- Also requires 'make' and other common build tools
