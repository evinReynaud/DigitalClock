#include <avr/io.h>
#include "spi.h"
#include <util/delay.h>

void main(void)
{
  SPI_MasterInit();
  while (1)
  {

    PORTE &= ~_BV(PE5);
    PORTE |= _BV(PE4);
    SPI_MasterTransmit(42);
    SPI_MasterTransmit(42);
    PORTE |= _BV(PE5);
    _delay_ms(1);
    PORTE &= ~_BV(PE5);
    PORTE &= ~_BV(PE4);
    _delay_ms(500);
    PORTE |= _BV(PE4);
  }
}
