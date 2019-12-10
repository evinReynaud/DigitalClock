#ifndef __EFFETHALL_H__
#define __EFFETHALL_H__

#include <stdint.h>

void effethall_init();

void check_effethall(void (*treatment)(), uint16_t timer);

#endif
