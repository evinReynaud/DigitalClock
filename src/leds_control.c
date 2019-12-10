#include <stdlib.h>
#include <string.h>

#include "leds.h"
#include "bluetooth.h"
#include "leds_control.h"

void leds_control()
{
  char buffer[256];
  bluetooth_wait_for_data(buffer);
  int num;
  if (strlen(buffer) >= 16)
    num = (int)strtol(buffer, NULL, 2);
  else
    num = (int)strtol(buffer, NULL, 16);
  leds_on(num);
  bluetooth_transmit(buffer);
}
