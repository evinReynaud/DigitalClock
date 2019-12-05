#ifndef __EFFETHALL_H__
#define __EFFETHALL_H__

#include <avr/interrupt.h>
#include <avr/io.h>

#define TRUE 1
#define FALSE 0

void effethall_init();
void check_effet_hall();

#endif
