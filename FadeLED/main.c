/*
  FadeLED

  Uses PWM to fade an LED in and out, repeatedly.
*/

#include <stdint.h>
#include <pdk/device.h>
#include "auto_sysclock.h"
#include "delay.h"

// Define which type of PWM to use
#if defined(PWMG1CUBL)            // Full 11-bit PWM:   PFS154,PMS154C
  #define PWM_11_FULL
#elif defined(PWMGCUBL)           // Basic 11-bit PWM:  PFS173,PMS152
  #define PWM_11_BASIC
#else                             // 8-bit PWM:         PFS172,PMS15A,PMS150C,PMC171B
  #define PWM_8
#endif

// Define which Pin the LED is on (current sink configuration)
#if defined(PWM_8)
  #define LED_PIN             3   // LED is placed on Port A, Pin 3, which is also TM2PWM
#else
  #define LED_PIN             4   // LED is placed on Port A, Pin 4, which is also PG1PWM
#endif

// Main program
void main() {

  // Initialize hardware
  PAC |= (1 << LED_PIN);          // Set LED_PIN as output (all pins are input by default)

#if defined(PWM_8)
  TM2B = 0x00;                    // Clear the LED PWM duty value
  TM2C = (uint8_t)(TM2C_INVERT_OUT | TM2C_MODE_PWM | TM2C_OUT_PA3 | TM2C_CLK_IHRC);
  TM2S = 0x00;                    // No pre-scaler, 8-bit
#elif defined(PWM_11_FULL)
  PWMG1DTL = 0x00;                // Clear the LED PWM duty value
  PWMG1DTH = 0x00;
  PWMG1CUBL = 0x00;               // Setup PWM upper bound
  PWMG1CUBH = 0xFF;
  PWMG1C = (uint8_t)(PWMG1C_ENABLE | PWMG1C_INVERT_OUT | PWMG1C_OUT_PA4 | PWMG1C_CLK_IHRC);
  PWMG1S = 0x00;                  // No pre-scaler
#else
  PWMG1DTL = 0x00;                // Clear the LED PWM duty value
  PWMG1DTH = 0x00;
  PWMGCUBL = 0x00;                // Setup PWM upper bound
  PWMGCUBH = 0xFF;
  PWMGCLK = (uint8_t)(PWMGCLK_PWMG_ENABLE | PWMGCLK_CLK_IHRC);
  PWMG1C = (uint8_t)(PWMG1C_INVERT_OUT | PWMG1C_OUT_PWMG1 | PWMG1C_OUT_PA4);
#endif

  // Main processing loop
  while (1) {
    uint8_t fadeValue;

    // Fade in from min to max in increments of 5
    for (fadeValue = 0; fadeValue < 255; fadeValue += 5) {
      #if defined(PWM_8)
        TM2B = fadeValue;         // Set the LED PWM duty value
      #else
        PWMG1DTH = fadeValue;     // Set the LED PWM duty value
      #endif
      _delay_ms(30);              // wait for 30 milliseconds to see the dimming effect
    }

    // Fade out from max to min in increments of 5
    for (fadeValue = 255; fadeValue > 0; fadeValue -= 5) {
      #if defined(PWM_8)
        TM2B = fadeValue;         // Set the LED PWM duty value
      #else
        PWMG1DTH = fadeValue;     // Set the LED PWM duty value
      #endif
      _delay_ms(30);              // wait for 30 milliseconds to see the dimming effect
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
