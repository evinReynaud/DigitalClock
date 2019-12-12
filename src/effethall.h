#ifndef __EFFETHALL_H__
#define __EFFETHALL_H__

#include <stdint.h>

extern volatile uint16_t countPerTour;
extern uint16_t effethall_timer;

void effethall_init();

void effethall_enable_interruption();

#endif
