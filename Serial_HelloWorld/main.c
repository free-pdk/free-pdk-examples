/*
  Serial_HelloWorld

  Transmits "Hello World" over Serial @ ~115200 baud, and repeats once a second.
*/

#include <pdk/device.h>
#include "sysclock.h"
#include "serial.h"
#include "delay.h"

// Note: serial.h assumes TX is on PA7, and uses timer2 (TM2) interrupts for timing.

void interrupt(void) __interrupt(0) {
  if (INTRQ & INTRQ_TM2) {        // TM2 interrupt request?
    INTRQ &= ~INTRQ_TM2;          // Mark TM2 interrupt request processed
    serial_irq_handler();         // Process next Serial Bit
  }
}

// Main program.
void main() {
  // Initialize hardware
  serial_setup();                 // Initialize Serial engine

  INTRQ = 0;
  __engint();                     // Enable global interrupts

  // Main processing loop.
  while(1) {
    serial_println("Hello World!");
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
