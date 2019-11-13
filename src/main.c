#include <avr/io.h>
#include "spi.h"
#include "bluetooth.h"

void main(void)
{
  SPI_MasterInit();
  Bluetooth_Init(MYUBRR);
  while (1)
  {
    char c = Bluetooth_Receive();
    Bluetooth_Transmit(c);
    SPI_MasterTransmit(0xf0f0);
  }}
