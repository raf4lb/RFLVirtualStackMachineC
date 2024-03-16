#include "io.h"
#include "avr/io.h"

void set_port(int address, int value) {
  switch (address) {
  case _DDRB:
    DDRB = value;
    break;
  case _PORTB:
    PORTB = value;
    break;
  default:
    break;
  }
}