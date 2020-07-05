/*
  ReadButton_WriteSerial

  Reads a Button (digital input), and transmits the results over Serial @ ~115200 baud.
*/

#include <pdk/device.h>
#include "sysclock.h"
#include "serial.h"
#include "delay.h"

// Note: serial.h assumes TX is on PA7, and uses timer2 (TM2) interrupts for timing.

// BTN is placed on PA5 (active low configuration)
#define BTN_PIN             5

#define isButtonActive()    !(PA & (1 << BTN_PIN))

uint8_t previousButtonState;

void interrupt(void) __interrupt(0) {
  if (INTRQ & INTRQ_TM2) {      // TM2 interrupt request?
    INTRQ &= ~INTRQ_TM2;        // Mark TM2 interrupt request processed
    serial_irq_handler();       // Process next Serial Bit
  }
}

// Main program.
void main() {
  // Initialize hardware
  //PAC &= ~(1 << BTN_PIN);         // Set BTN_PIN as input (all pins are input by default)
  PADIER |= (1 << BTN_PIN);       // Enable BTN_PIN as digital input
  PAPH |= (1 << BTN_PIN);         // Enable pull-up resistor on BTN_PIN

  serial_setup();                 // Initialize Serial engine

  INTRQ = 0;
  __engint();                     // Enable global interrupts

  // Main processing loop.
  while(1) {
    uint8_t buttonState = isButtonActive();
      if (buttonState != previousButtonState) {
      if (buttonState) {
        serial_println("Button Down");
      } else {
        serial_println("Button Up");
      }
      previousButtonState = buttonState;
    }
    _delay_ms(1);                 // Short delay (i.e. debounce button)
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
