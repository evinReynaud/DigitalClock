#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

#include "spi.h"
#include "bluetooth.h"

void main(void)
{
  SPI_MasterInit();
  //Bluetooth_Init(MYUBRR);
  while (TRUE)
  {

    char buffer[256];
    Bluetooth_Receive(buffer);
    int num;
    if(strlen(buffer) >= 16)
      num = (int) strtol(buffer, NULL, 2);
    else
      num = (int) strtol(buffer, NULL, 16);
    char c1 = (char) (num >> 8);
    char c2 = (char) num;
    SPI_MasterTransmit(num);
    Bluetooth_Transmit(buffer);
  }
}
