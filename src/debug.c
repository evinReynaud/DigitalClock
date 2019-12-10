#include "bluetooth.h"

#include "debug.h"

void debug_printf(char * b){
  bluetooth_transmit(b);
}

void debug_wait_input(){
  char b[2];
  bluetooth_wait_for_data(b);
}
