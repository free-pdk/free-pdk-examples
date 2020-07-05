# free-pdk-examples
Code Examples for Padauk MCUs using the free-pdk toolchain

### Examples:
- **01. Basics:**
  - [Blink](01.Basics/Blink) - Turns an LED on for one second, then off for one second, repeatedly.
  - [Fade](01.Basics/Fade) - Uses PWM to fade an LED in and out, repeatedly.

### Toolchain:
- SDCC Compiler: [SDCC](http://sdcc.sourceforge.net/) (3.9.0 or newer - 4.0.0+ preferred)
- Easy PDK Programmer: [easy-pdk-programmer-software](https://github.com/free-pdk/easy-pdk-programmer-software) (v1.3 or newer. Currently in development branch)
- PDK device includes: [pdk-includes](https://github.com/free-pdk/pdk-includes)
  - Integrated as git Submodule
- Easy PDK Programmer includes: [easy-pdk-includes](https://github.com/free-pdk/easy-pdk-includes)
  - Integrated as git Submodule
- Also requires 'make' and other common build tools
