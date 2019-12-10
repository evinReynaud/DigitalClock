#ifndef __CLOCK_H__
#define __CLOCK_H__
#include <stdint.h>

extern volatile int8_t hours;
extern volatile int8_t minutes;
extern volatile uint8_t seconds;

void update_hour();

#endif