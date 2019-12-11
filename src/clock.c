#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"
#include "display.h"

#include "debug.h"

#include "clock.h"

volatile int8_t hours = -1;
volatile int8_t minutes = -1;

char hour_changed = 0;
char minute_changed = 0;
uint8_t check_seconds = 0;
char send = 0;

void update_hour()
{
  if (seconds == 0 && minute_changed == 0)
  {
    minutes = (minutes + 1) % 60;
    minute_changed = 1;
  }
  else if (seconds == 1)
  {
    minute_changed = 0;
  }
  if (minutes == 0 && hour_changed == 0)
  {
    hours = (hours + 1) % 24;
    hour_changed = 1;
  }
  else if (minutes == 1)
  {
    hour_changed = 0;
  }

  if (check_seconds != seconds)
  {
    check_seconds = seconds;
    compute_display();
  }
}
