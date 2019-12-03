#include "leds.h"
#include "bluetooth.h"
#include "test.h"
#include "display_analog.h"

int main()
{
  leds_init();
  bluetooth_init();
  test_init();

  while (1)
  {
    display_strip();
    get_values();
  }
  return 0;
}
