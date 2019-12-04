#include "leds.h"
#include "bluetooth.h"
#include "display_analog.h"
#include "clock.h"
#include "interface.h"

#include "test.h"

int main()
{
  leds_init();
  bluetooth_init();

  while (1)
  {
    interface();
    update_hour();
    display_strip();
  }
  return 0;
}
