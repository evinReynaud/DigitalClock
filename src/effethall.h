#ifndef __EFFETHALL_H__
#define __EFFETHALL_H__

#include <stdint.h>

extern volatile uint16_t countPerTour;
extern volatile int force_hall;

void effethall_init();

void check_effethall();

#endif
