#ifndef __POS_TIMER_H__
#define __POS_TIMER_H__

#include <stdint.h>

void pos_timer_init();

void pos_timer_stop();

void pos_timer_start();

uint16_t pos_timer_read();
void pos_timer_write(uint16_t val);

#endif
