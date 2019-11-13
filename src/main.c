#include <util/delay.h>

#include "bluetooth.h"

void main()
{
  Bluetooth_Init(MYUBRR);

  while (TRUE)
  {
    char c = Bluetooth_Receive();
    Bluetooth_Transmit(c);
  }
  return;
}
