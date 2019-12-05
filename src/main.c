#include "leds.h"
#include "bluetooth.h"
#include "display_analog.h"
#include "clock.h"
#include "interface.h"
#include "position.h"
#include "effethall.h"

int main()
{
  timer_init_postion();
  timer_start_position();
  bluetooth_init();
  effethall_init();
  SPI_master_init();

  while (1)
  {
    interface();
    update_hour();
    display_strip();
    check_effet_hall();
  }
  return 0;
}
