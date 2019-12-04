#ifndef __CLOCK_H__
#define __CLOCK_H__
#include <stdint.h>

int8_t extern minutes;
int8_t extern hours;
volatile uint8_t extern seconds;

void update_hour();

#endif