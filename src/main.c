#include "leds.h"
#include "bluetooth.h"
#include "leds_control.h"
#include "interface.h"

void main(void)
{
  leds_init();
  bluetooth_init();
  send_info();
  while (TRUE)
  {
    interface();
  }
}
