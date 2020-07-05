/*
  FadeLED

  Uses PWM to fade an LED in and out, repeatedly.
*/

#include <stdint.h>
#include <pdk/device.h>
#include "sysclock.h"
#include "delay.h"

// LED is placed on PA4/PG1PWM (current sink configuration)
#define LED_PIN             4

int16_t brightness = 0;           // How bright the LED is
int8_t fadeAmount = 5;            // How many points to fade the LED by

// Main program.
void main() {
  // Initialize hardware
  PAC |= (1 << LED_PIN);          // Set LED_PIN as output (all pins are input by default)

  PWMG1DTL = 0x00;                // Clear the LED PWM duty value
  PWMG1DTH = 0x00;

#if defined(PWMG1CUBL)
  PWMG1CUBL = 0xFF;               // Setup PWM upper bound
  PWMG1CUBH = 0x00;
  PWMG1C = (uint8_t)(PWMG1C_ENABLE | PWMG1C_INVERT_OUT | PWMG1C_OUT_PA4 | PWMG1C_CLK_IHRC);
#else
  PWMGCUBL = 0x00;                // Setup PWM upper bound
  PWMGCUBH = 0xFF;
  PWMGCLK = (uint8_t)(PWMGCLK_PWMG_ENABLE | PWMGCLK_CLK_IHRC);
  PWMG1C = (uint8_t)(PWMG1C_INVERT_OUT | PWMG1C_OUT_PWMG1 | PWMG1C_OUT_PA4);
#endif

  // Main processing loop.
  while(1) {
    PWMG1DTH = brightness;        // Set the LED PWM duty value

    brightness += fadeAmount;
    if (brightness + fadeAmount <= 0 || brightness > 255) {
      fadeAmount = -fadeAmount;
      brightness += fadeAmount;
    }

    _delay_ms(30);
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
