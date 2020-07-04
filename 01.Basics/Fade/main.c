/*
  Fade

  Uses PWM to fade an LED in and out.
*/

#include "pdk/device.h"
#include "easy-pdk/calibrate.h"
#include "delay.h"

// LED is placed on PA4/PG1PWM (current sink configuration)
#define LED_PIN         4

int16_t brightness = 0;         // how bright the LED is
int8_t fadeAmount = 5;          // how many points to fade the LED by

// Main hardware initialization.
inline void setup() {
  PAC |= (1 << LED_PIN);        // Set LED_PIN as output (all pins are input by default)

#if defined(PWMG1CUBL)
  PWMG1C = 0b10100111;          // Setup PWM (Enable PWMG1, Inverse Polarity, PA4 output, IHRC source)
  PWMG1CUBL = 0xFF;             // Setup PWM upper bound
  PWMG1CUBH = 0x00;
#else
  PWMGCLK = 0b10000001;         // Setup PWM (Enable PWM, IHRC source)
  PWMGCUBL = 0x00;              // Setup PWM upper bound
  PWMGCUBH = 0xFF;
  PWMG1C = 0b00100110;          // Setup PWM (Inverse Polarity, PWMG1/PA4 output)
#endif
  PWMG1DTL = 0x00;              // Set the LED PWM duty value
  PWMG1DTH = 0x00;
}

// Main processing loop.
inline void loop() {
  PWMG1DTH = brightness;        // Set LED PWM duty value

  brightness += fadeAmount;
  if (brightness + fadeAmount <= 0 || brightness > 255) {
    fadeAmount = -fadeAmount;
    brightness += fadeAmount;
  }

  _delay_ms(30);
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

#if (F_CPU == 8000000)
  PDK_USE_8MHZ_IHRC_SYSCLOCK();
  EASY_PDK_CALIBRATE_IHRC(F_CPU, TARGET_VDD_MV);
#elif (F_CPU == 4000000)
  PDK_USE_4MHZ_IHRC_SYSCLOCK();
  EASY_PDK_CALIBRATE_IHRC(F_CPU, TARGET_VDD_MV);
#elif (F_CPU == 2000000)
  PDK_USE_2MHZ_IHRC_SYSCLOCK();
  EASY_PDK_CALIBRATE_IHRC(F_CPU, TARGET_VDD_MV);
#elif (F_CPU == 1000000)
  PDK_USE_1MHZ_IHRC_SYSCLOCK();
  EASY_PDK_CALIBRATE_IHRC(F_CPU, TARGET_VDD_MV);
#else
  #error "Unknown F_CPU"
#endif

  return 0;
}
