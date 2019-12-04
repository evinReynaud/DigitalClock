#ifndef __TIMER_H__
#define __TIMER_H__

volatile uint16_t time_count;
volatile uint8_t seconds;

void timer_init();

void timer_start();

void timer_stop();

#endif