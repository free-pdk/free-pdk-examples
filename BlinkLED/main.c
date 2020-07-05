/*
  BlinkLED

  Turns an LED on for one second, then off for one second, repeatedly.
  Uses a timing loop for delays.
*/

#include <pdk/device.h>
#include "sysclock.h"
#include "delay.h"

// LED is placed on PA4 (current sink configuration)
#define LED_PIN             4

#define turnLedOn()         PA &= ~(1 << LED_PIN)
#define turnLedOff()        PA |= (1 << LED_PIN)

// Main program.
void main() {
  // Initialize hardware
  PAC |= (1 << LED_PIN);          // Set LED_PIN as output (all pins are input by default)
  turnLedOff();

  // Main processing loop.
  while(1) {
    turnLedOn();
    _delay_ms(1000);
    turnLedOff();
    _delay_ms(1000);
  }
}

// Startup code - Setup/calibrate system clock.
unsigned char _sdcc_external_startup(void) {
  // Modify F_CPU in the Makefile to change frequencies
  // ...or... Replace these with the more specific PDK_SET_SYSCLOCK(...) / EASY_PDK_CALIBRATE_IHRC(...) macros.
  // See pdk/sysclock.h for details.
  FREE_PDK_INIT_SYSCLOCK();
  FREE_PDK_CALIBRATE_SYSCLOCK(TARGET_VDD_MV);
  return 0;
}
