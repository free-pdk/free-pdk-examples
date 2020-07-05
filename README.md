# free-pdk-examples
Code Examples for Padauk MCUs using the free-pdk toolchain

### Code Examples:
- [**BlinkLED**](BlinkLED) - Turns an LED on for one second, then off for one second, repeatedly.  Uses a timing loop for delays.
- **BlinkLED_WithIRQ** (TODO...) - Turns an LED on for one second, then off for one second, repeatedly.  Uses a timer interrupt for delays.
- [**FadeLED**](FadeLED) - Uses PWM to fade an LED in and out, repeatedly.
- [**ReadButton_WriteLED**](ReadButton_WriteLED) - Reads a Button (digital input), and turns on an LED when active.
- [**Serial_HelloWorld**](Serial_HelloWorld) - Transmits "Hello World" over Serial @ ~115200 baud, and repeats once a second.
- [**ReadButton_WriteSerial**](ReadButton_WriteSerial) - Reads a Button (digital input), and transmits the results over Serial @ ~115200 baud.
- **ReadAnalog_FadeLED** (TODO...) - Reads an Analog input, and uses PWM to set the brightness of an LED.
- **ReadAnalog_WriteSerial** (TODO...) - Reads an Analog input, and transmits the results over Serial @ ~115200 baud. 
- **ReadAnalog_WriteAverageSerial** (TODO...) - Reads an analog input, calculates a rolling average, and transmits the results over Serial @ ~115200 baud.
- **EchoSerial** (TODO...) - Echos back over Serial every line that is received.
- **ReadSerial_FadeLED** (TODO...) - Reads a value over Serial, and uses PWM to set the brightness of an LED.

### Toolchain:
- SDCC Compiler: [SDCC](http://sdcc.sourceforge.net/) (3.9.0 or newer - 4.0.0+ preferred)
- Easy PDK Programmer: [easy-pdk-programmer-software](https://github.com/free-pdk/easy-pdk-programmer-software) (v1.3 or newer. Currently in development branch)
- PDK device includes: [pdk-includes](https://github.com/free-pdk/pdk-includes)
  - Integrated as git Submodule
- Easy PDK Programmer includes: [easy-pdk-includes](https://github.com/free-pdk/easy-pdk-includes)
  - Integrated as git Submodule
- Also requires 'make' and other common build tools
