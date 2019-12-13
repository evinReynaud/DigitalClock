#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdint.h>

extern int8_t hours;
extern int8_t minutes;

#ifndef __TIMER_H__
extern volatile uint8_t seconds;
#endif

void update_time();
void set_time(int8_t h, int8_t m, int8_t s);

#endif
