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
    SPI_MasterTransmit(8);
    SPI_MasterTransmit(8);
    PORTE |= _BV(PE5);
    PORTE &= ~_BV(PE5);
    PORTE &= ~_BV(PE4);
    _delay_ms(500);
    PORTE |= _BV(PE4);
  }
}
