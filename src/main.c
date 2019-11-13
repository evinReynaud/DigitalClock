#include <avr/io.h>
#include "spi.h"

void main(void)
{
  SPI_MasterInit();
  while (1)
  {
    SPI_MasterTransmit(0xf0f0);
  }
}
