/*
  BlinkLED_WithIRQ

  Turns an LED on for one second, then off for one second, repeatedly.
  Uses a timer interrupt for delays.
*/

#include <stdint.h>
#include <pdk/device.h>
#include "auto_sysclock.h"
#include "millis.h"

// Note: millis.h uses timer16 (T16) interrupts for timekeeping.

// LED is placed on the PA4 pin (Port A, Bit 4) with a current sink configuration
#define LED_BIT             4

// LED is active low (current sink), so define helpers for better readability below
#define turnLedOn()         PA &= ~(1 << LED_BIT)
#define turnLedOff()        PA |= (1 << LED_BIT)
#define toggleLed()         PA ^= (1 << LED_BIT)

// Interval at which to blink the LED (milliseconds)
#define BLINK_INTERVAL      1000

uint32_t previousMillis;          // The last time the LED was updated

void interrupt(void) __interrupt(0) {
  if (INTRQ & INTRQ_T16) {        // T16 interrupt request?
    INTRQ &= ~INTRQ_T16;          // Mark T16 interrupt request processed
    millis_irq_handler();
  }
}

// Main program
void main() {

  // Initialize hardware
  PAC |= (1 << LED_BIT);          // Set LED as output (all pins are input by default)
  turnLedOff();

  millis_setup();

  INTRQ = 0;
  __engint();                     // Enable global interrupts

  // Main processing loop
  while (1) {
    uint32_t currentMillis = millis();
    if (currentMillis - previousMillis > BLINK_INTERVAL) {
      toggleLed();
      previousMillis += BLINK_INTERVAL;
    }
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
