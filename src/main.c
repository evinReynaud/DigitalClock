#include "bluetooth.h"

void main() {
  Bluetooth_Init(MYUBRR);

  while(1){
    char c = Bluetooth_Receive();
    Bluetooth_Transmit(c);
  }
  return;
}
