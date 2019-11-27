#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"

void main()
{
  leds_init();
  timer_init();
  bluetooth_init();
  timer_start();

  leds_on(0xffff);
  while(1) {
    if(tic == 1) {
      leds_on(0);
    } else {
      leds_on(0xffff);
    }
  }
}
