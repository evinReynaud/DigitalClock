#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"
#include "display_analog.h"

#include "debug.h"

#include "clock.h"


char minute_change = 0;
char hour_change = 0;
char send = 0;
uint8_t check_seconds = 0;
volatile int8_t minutes = -1;
volatile int8_t hours = -1;

void update_hour()
{

    if (seconds == 0 && minute_change == 0)
    {
        minutes = (minutes + 1) % 60;
        minute_change = 1;
    }
    if (seconds == 1)
    {
        minute_change = 0;
    }
    if (minutes == 0 && hour_change == 0)
    {
        hours = (hours + 1) % 24;
        hour_change = 1;
    }
    if (minutes == 1)
    {
        hour_change = 0;
    }

    if (check_seconds != seconds)
    {
        check_seconds = seconds;
        compute_display();
    }
}