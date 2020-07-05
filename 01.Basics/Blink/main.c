/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.
*/

#include <pdk/device.h>
#include <easy-pdk/calibrate.h>
#include "sysclock.h"
#include "delay.h"

// LED is placed on PA4 (current sink configuration)
#define LED_PIN         4

// Main hardware initialization.
inline void setup() {
  PAC |= (1 << LED_PIN);        // Set LED_PIN as output (all pins are input by default)
  PA |= (1 << LED_PIN);         // Turn LED off (i.e. write pin high)
}

// Main processing loop.
inline void loop() {
  PA &= ~(1 << LED_PIN);        // Turn LED on (i.e. write pin low)
  _delay_ms(1000);
  PA |= (1 << LED_PIN);         // Turn LED off (i.e. write pin high)
  _delay_ms(1000);
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
