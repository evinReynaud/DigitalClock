#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

extern volatile uint8_t seconds;

void timer_init();

void timer_start();

void timer_stop();

#endif
