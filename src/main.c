#include "leds.h"
#include "bluetooth.h"
#include "display_analog.h"
#include "clock.h"
#include "interface.h"
#include "position.h"
#include "effethall.h"

#include "debug.h"

int main()
{
  bluetooth_init();
  debug_printf("Start init\n");
  timer_init_postion();
  timer_start_position();
  effethall_init();
  SPI_master_init();

  leds_on(0xffff);

  debug_printf("Init done\n");

  leds_on(LEDS_OFF);
  debug_printf("Lights off\n");
  //debug_wait_input();
  debug_printf("Lights on\n");

  while (1)
  {
    //leds_on(0xffff);
    // interface();
    // update_hour();
    // display_strip();
    // check_effet_hall();
  }
  return 0;
}
