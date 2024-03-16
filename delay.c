#define F_CPU 16000000UL
#include <util/delay.h> // Delay functions

void delay_ms(int milliseconds) {
  while (milliseconds > 0) {
    _delay_ms(1); // Delay 1 millisecond using built-in _delay_ms function
    milliseconds--;
  }
}
