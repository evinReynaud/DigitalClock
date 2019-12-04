#include "leds.h"
#include "bluetooth.h"
#include "leds_control.h"

void main(void)
{
  leds_init();
  bluetooth_init();
  while (TRUE)
  {
    leds_control();
  }
}
