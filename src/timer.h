#ifndef __TIMER_H__
#define __TIMER_H__

volatile int time_count;
volatile int tic;

void timer_init();

void timer_start();

void timer_stop();

#endif
