/*
  BlinkLED_WithIRQ

  Turns an LED on for one second, then off for one second, repeatedly.
  Uses a timer interrupt for delays.
*/

#include <stdint.h>
#include <pdk/device.h>
#include "sysclock.h"
#include "millis.h"

// Note: millis.h uses timer16 (T16) interrupts for timing.

// LED is placed on PA4 (current sink configuration)
#define LED_PIN             4

#define turnLedOn()         PA &= ~(1 << LED_PIN)
#define turnLedOff()        PA |= (1 << LED_PIN)
#define toggleLed()         PA ^= (1 << LED_PIN)

uint32_t previousMillis;

void interrupt(void) __interrupt(0) {
  if (INTRQ & INTRQ_T16) {      // T16 interrupt request?
    INTRQ &= ~INTRQ_T16;        // Mark T16 interrupt request processed
    millis_irq_handler();
  }
}

// Main hardware initialization.
inline void setup() {
  PAC |= (1 << LED_PIN);        // Set LED_PIN as output (all pins are input by default)
  turnLedOff();

  millis_setup();

  INTRQ = 0;
  __engint();                   // Enable global interrupts
}

// Main processing loop.
inline void loop() {
  if (millis - previousMillis >= 1000) {
    toggleLed();
    previousMillis += 1000;
  }
}

// Main program.
void main() {
  setup();
  while(1) {
    loop();
  }
}

// Startup code - Setup/calibrate system clock.
unsigned char _sdcc_external_startup(void) {
  FREE_PDK_INIT_SYSCLOCK();
  FREE_PDK_CALIBRATE_SYSCLOCK(TARGET_VDD_MV);
  return 0;
}
