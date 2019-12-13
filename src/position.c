#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "interface.h"
#include "config.h"
#include "pos_timer.h"
#include "effethall.h"

#include "position.h"

int offset = 0;

void position_init()
{
  pos_timer_init();
  effethall_init();
  pos_timer_start();
}

uint32_t get_pos()
{
  uint32_t t = (uint32_t) pos_timer_read();
  return (offset + (t*POS_IN_A_TURN/countPerTour))%POS_IN_A_TURN;
}

inline void check_position()
{
  effethall_enable_interruption();
}
