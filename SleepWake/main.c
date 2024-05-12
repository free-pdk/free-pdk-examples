/*
  SleepWake

  Blinks an LED to indicate that it's active, then goes to sleep to
  preserve power.

  Processor will wake when PA0 sees any level change.

  Note: When supplied with more than 3v the current draw may be higher
  than the datasheet claims (13uA instead of 0.5uA my testing).

  This appnote suggests it's due to internal leakage between PA5 and GND
  https://www.padauk.com.tw/upload/ApplicationNote/APN012_PMS150B_Power_Saving_Mode_v001_EN.pdf
*/

#include <pdk/device.h>
#include "auto_sysclock.h"
#include "startup.h"
#include "delay.h"

#define sleep() __asm stopsys __endasm;

// LED is placed on the PA4 pin (Port A, Bit 4) with a current sink configuration
#define LED_BIT             4
#define SW_BIT              0

// LED is active low (current sink), so define helpers for better readability below
#define turnLedOn()         PA &= ~(1 << LED_BIT)
#define turnLedOff()        PA |= (1 << LED_BIT)

void setup(void) {
  PAC &= ~(1<<SW_BIT); // Set button as input
  PADIER |= 1<<SW_BIT; // Enable button for waking up
}

// Main program
void main(void) {

  // Initialize hardware
  PAC |= (1 << LED_BIT);          // Set LED as output (all pins are input by default)

  turnLedOff();
  setup();

  // Main processing loop
  while (1) 
  {
    for (int i = 0; i < 3; i++) {
      turnLedOn();
      _delay_ms(400);
      turnLedOff();
      _delay_ms(400);
    }

    //sleep();
  }
}

// Startup code - Setup/calibrate system clock
unsigned char STARTUP_FUNCTION(void) {

  // Initialize the system clock (CLKMD register) with the IHRC, ILRC, or EOSC clock source and correct divider.
  // The AUTO_INIT_SYSCLOCK() macro uses F_CPU (defined in the Makefile) to choose the IHRC or ILRC clock source and divider.
  // Alternatively, replace this with the more specific PDK_SET_SYSCLOCK(...) macro from pdk/sysclock.h
  AUTO_INIT_SYSCLOCK();
  //CLKMD = 0b11000100;

  // Insert placeholder code to tell EasyPdkProg to calibrate the IHRC or ILRC internal oscillator.
  // The AUTO_CALIBRATE_SYSCLOCK(...) macro uses F_CPU (defined in the Makefile) to choose the IHRC or ILRC oscillator.
  // Alternatively, replace this with the more specific EASY_PDK_CALIBRATE_IHRC(...) or EASY_PDK_CALIBRATE_ILRC(...) macro from easy-pdk/calibrate.h
  AUTO_CALIBRATE_SYSCLOCK(TARGET_VDD_MV);

  return 0;   // Return 0 to inform SDCC to continue with normal initialization.
}
