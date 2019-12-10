#include "leds.h"
#include "bluetooth.h"
#include "display_analog.h"
#include "clock.h"
#include "interface.h"
#include "position.h"

#include "debug.h"

int main()
{
  bluetooth_init();
  debug_printf("Start init\n");
  position_init();
  leds_init();
  timer_start();
  send_info();
  interface_interrupt_init();

  leds_on(0xffff);

  debug_printf("Init done\n");

  leds_on(LEDS_OFF);
  debug_printf("Lights off\n");
  //debug_wait_input();
  debug_printf("Lights on\n");

  while (1)
  {
    //leds_on(0xffff);
    interface();
    update_hour();
    display_strip();
  }
  return 0;
}
