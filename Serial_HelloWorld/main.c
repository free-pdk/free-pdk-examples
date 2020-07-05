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
  if (INTRQ & INTRQ_TM2) {      // TM2 interrupt request?
    INTRQ &= ~INTRQ_TM2;        // Mark TM2 interrupt request processed
    serial_irq_handler();       // Process next Serial Bit
  }
}

// Main hardware initialization.
inline void setup() {
  serial_setup();               // Initialize Serial engine

  INTRQ = 0;
  __engint();                   // Enable global interrupts
}

// Main processing loop.
inline void loop() {
  serial_println("Hello World!");
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
