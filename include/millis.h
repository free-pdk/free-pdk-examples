#ifndef __MILLIS_H__
#define __MILLIS_H__

#include <stdint.h>

volatile uint8_t _ticks;
volatile uint32_t _millis;                       // Number of elapsed milliseconds

void millis_setup() {
  // Setup timer16 (T16) interrupt to tick every 32 uS
  T16M = (uint8_t)(T16M_CLK_IHRC | T16M_CLK_DIV1 | T16M_INTSRC_8BIT);
  T16C = 0;
  INTEN |= INTEN_T16;
}

uint32_t millis() {
  INTEN &= ~INTEN_T16;                          // Disable T16 (read of 32 bit value _millis is non-atomic)
  uint32_t currentMillis = _millis;
  INTEN |= INTEN_T16;                           // Re-enable T16
  return currentMillis;
}

void millis_irq_handler() {
  if (_ticks++ == 31) { // Should really be 31.25, but close enough?
    _ticks = 0;
    _millis++;
  }
}

#endif //__SERIAL_H__
