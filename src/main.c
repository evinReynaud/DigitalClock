#include "bluetooth.h"
#include "leds_control.h"
#include "interface.h"
#include "timer.h"
#include "clock.h"

int main()
{
  timer_init();
  bluetooth_init();
  timer_start();
  send_info();
  interface_interrupt_init();

  while (TRUE)
  {
    interface();
    update_hour();
  }
  return 0;
}
