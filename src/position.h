#ifndef __POSITION_H__
#define __POSITION_H__

#include <stdint.h>

extern int offset;

void position_init();

uint32_t get_pos();

void check_position();

#endif
