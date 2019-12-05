#include "spi.h"

#include "leds.h"

void leds_init()
{
  SPI_master_init();
}

void leds_on(unsigned int data)
{
  char c1 = (char) (data >> 8);
  char c2 = (char) data;

  SPI_master_transmit_char(c1);
  SPI_master_transmit_char(c2);
  SPI_master_EOC();
}
