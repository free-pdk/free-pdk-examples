/*
  Serial_HelloWorld

  Transmits "Hello World" over Serial @ ~115200 baud, and repeats once a second.
*/

#include <pdk/device.h>
#include "auto_sysclock.h"
#include "startup.h"
#include "serial.h"
#include "delay.h"

// Note: serial.h assumes TX is on the PA7 pin (Port A, Bit 7), and uses timer2 (TM2) interrupts for timing.

void interrupt(void) __interrupt(0) {
  if (INTRQ & INTRQ_TM2) {        // TM2 interrupt request?
    INTRQ &= ~INTRQ_TM2;          // Mark TM2 interrupt request processed
    serial_irq_handler();         // Process next Serial Bit
  }
}

// Main program
void main() {

  // Initialize hardware
  serial_setup();                 // Initialize Serial engine

  INTRQ = 0;
  __engint();                     // Enable global interrupts

  // Main processing loop
  while (1) {
    serial_println("Hello World!");
    _delay_ms(1000);
  }
}

// Startup code - Setup/calibrate system clock
unsigned char STARTUP_FUNCTION(void) {

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
