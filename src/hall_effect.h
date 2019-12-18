#ifndef __EFFETHALL_H__
#define __EFFETHALL_H__

#include <stdint.h>

extern volatile uint16_t countPerTour;
extern uint16_t hall_effect_timer;

void hall_effect_init();

void hall_effect_enable_interruption();

#endif
