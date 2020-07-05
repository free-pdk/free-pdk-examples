/*
  ReadButton_WriteLED

  Reads a Button (digital input), and turns on an LED when active.
*/

#include <pdk/device.h>
#include "sysclock.h"
#include "delay.h"

// BTN is placed on PA5 (active low configuration)
#define BTN_PIN             5

#define isButtonActive()    !(PA & (1 << BTN_PIN))

// LED is placed on PA4 (current sink configuration)
#define LED_PIN             4

#define turnLedOn()         PA &= ~(1 << LED_PIN)
#define turnLedOff()        PA |= (1 << LED_PIN)

// Main hardware initialization.
inline void setup() {
  //PAC &= ~(1 << BTN_PIN);       // Set BTN_PIN as input (all pins are input by default)
  PADIER |= (1 << BTN_PIN);     // Enable BTN_PIN as digital input
  PAPH |= (1 << BTN_PIN);       // Enable pull-up resistor on BTN_PIN

  PAC |= (1 << LED_PIN);        // Set LED_PIN as output (all pins are input by default)
  turnLedOff();
}

// Main processing loop.
inline void loop() {

  if (isButtonActive()) {
    turnLedOn();
  } else {
    turnLedOff();
  }

  _delay_ms(1);                 // Short delay (i.e. debounce Button)
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
  // Modify F_CPU in the Makefile to change frequencies
  // ...or... Replace these with the more specific PDK_SET_SYSCLOCK(...) / EASY_PDK_CALIBRATE_IHRC(...) macros.
  // See pdk/sysclock.h for details.
  FREE_PDK_INIT_SYSCLOCK();
  FREE_PDK_CALIBRATE_SYSCLOCK(TARGET_VDD_MV);
  return 0;
}
