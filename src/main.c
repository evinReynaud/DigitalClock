#include "spi.h"
#include "bluetooth.h"
#include "leds_control.h"

void main(void)
{
  SPI_MasterInit();
  Bluetooth_Init(MYUBRR);
  while(1) {
    leds_control();
  }
}
