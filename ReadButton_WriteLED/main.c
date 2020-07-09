/*
  ReadButton_WriteLED

  Reads a Button (digital input), and turns on an LED when active.
*/

#include <pdk/device.h>
#include "auto_sysclock.h"
#include "delay.h"

// BTN is placed on Port A, Pin 5 (active low configuration)
#define BTN_PIN             5

// BTN is active low, so define helper for better readability below
#define isButtonActive()    !(PA & (1 << BTN_PIN))

// LED is placed on Port A, Pin 4 (current sink configuration)
#define LED_PIN             4

// LED is active low (current sink), so define helpers for better readability below
#define turnLedOn()         PA &= ~(1 << LED_PIN)
#define turnLedOff()        PA |= (1 << LED_PIN)

// Main program
void main() {

  // Initialize hardware
  //PAC &= ~(1 << BTN_PIN);         // Set BTN_PIN as input (all pins are input by default)
  PADIER |= (1 << BTN_PIN);       // Enable BTN_PIN as digital input
  PAPH |= (1 << BTN_PIN);         // Enable pull-up resistor on BTN_PIN

  PAC |= (1 << LED_PIN);          // Set LED_PIN as output (all pins are input by default)
  turnLedOff();

  // Main processing loop
  while (1) {
    if (isButtonActive()) {
      turnLedOn();
    } else {
      turnLedOff();
    }
    _delay_ms(1);                 // Short delay (i.e. debounce Button)
  }
}

// Startup code - Setup/calibrate system clock
unsigned char _sdcc_external_startup(void) {

  // Initialize the system clock (CLKMD register) with the IHRC, ILRC, or EOSC clock source and correct divider.
  // The AUTO_INIT_SYSCLOCK() macro uses F_CPU (defined in the Makefile) to choose the IHRC or ILRC clock source and divider.
  // Alternatively, replace this with the more specific PDK_SET_SYSCLOCK(...) macro from pdk/sysclock.h
  AUTO_INIT_SYSCLOCK();

  // Insert placeholder code to tell EasyPdkProg to calibrate the IHRC or ILRC internal oscillator.
  // The AUTO_CALIBRATE_SYSCLOCK(...) macro uses F_CPU (defined in the Makefile) to choose the IHRC or ILRC oscillator.
  // Alternatively, replace this with the more specific EASY_PDK_CALIBRATE_IHRC(...) or EASY_PDK_CALIBRATE_ILRC(...) macro from easy-pdk/calibrate.h
  AUTO_CALIBRATE_SYSCLOCK(TARGET_VDD_MV);

  return 0;   // Return 0 to inform SDCC to continue with normal initialization.
}
