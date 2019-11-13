#include <avr/io.h>
#include "spi.h"
#include "bluetooth.h"

void main(void)
{
  SPI_MasterInit();
  //Bluetooth_Init(MYUBRR);
  while (TRUE)
  {
    char c = Bluetooth_Receive();
    Bluetooth_Transmit(c);
    SPI_MasterTransmit(0b1111101111111110); // IMPORTANT : the first bit is the last led
  }
}
