#include "leds.h"

void main(void)
{
  leds_init();
  while(1)
  {
    leds_on(0b1000000011111110);
  }
}
