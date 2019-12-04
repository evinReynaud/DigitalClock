#include "leds.h"
#include "bluetooth.h"
#include "leds_control.h"
#include "interface.h"
#include "timer.h"
#include "clock.h"

void main(void)
{
  timer_init();
  bluetooth_init();
  timer_start();
  send_info();

  while (TRUE)
  {
    interface();
    update_hour();
  }
}
