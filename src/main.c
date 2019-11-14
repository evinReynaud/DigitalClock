#include "bluetooth.h"

void main()
{
  bluetooth_init();

  while(1){
    char buffer[256];
    bluetooth_receive(buffer);
    bluetooth_transmit(buffer);
  }
}
