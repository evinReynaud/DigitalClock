#include "leds.h"
#include "bluetooth.h"
#include "test.h"
#include "display_analog.h"

void main(void)
{
  leds_init();
  bluetooth_init();
  test_init();

  char b[24];
  while (1)
  {
    display_strip();
    get_values();
  }
}
