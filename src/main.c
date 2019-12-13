#include "leds.h"
#include "bluetooth.h"
#include "display.h"
#include "clock.h"
#include "config.h"
#include "interface.h"
#include "position.h"
#include "timer.h"
#include "effethall.h"
#include "debug.h"

void system_init()
{
  mode = ANALOG;
  hours = 0;
  minutes = 0;
  seconds = 0;
  bluetooth_init();
  debug_printf("=================\nStart init\n");
  debug_printf("Init leds\n");
  leds_init();
  leds_on(0xffff);
  debug_printf("Init timer\n");
  timer_init();
  debug_printf("Init position\n");
  position_init();
  debug_printf("Init display\n");
  init_display();
  debug_printf("Start timer\n");
  timer_start();

  leds_on(LEDS_OFF);

  debug_printf("Init done\n\n");
}

void soft_reset()
{
  mode = ANALOG;
  hours = 0;
  minutes = 0;
  seconds = 0;
  init_display();
  position_init();
}

int main()
{
  system_init();
  send_info();
  while (1)
  {
    if (reset == 1)
    {
      reset = 0;
      soft_reset();
    }
    if (reset == 2)
    {
      reset = 0;
      system_init();
    }
    interface();
    update_time();
    display_strip();

    check_position();
  }
  return 0;
}
