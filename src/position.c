#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "config.h"
#include "pos_timer.h"
#include "effethall.h"

#include "bluetooth.h"
#include "debug.h"

#include "position.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

inline int abs(int x) {
  return (x >= 0) ? x : -x;
}

void position_init()
{
  pos_timer_init();
  effethall_init();
  pos_timer_start();
}

uint32_t get_pos()
{
  // char b[20];
  // sprintf(b, "%u, %u\n", pos_timer_read(), countPerTour);
  // debug_printf(b);
  // return (int)(pos_timer_read()-countPerTour);
  uint32_t t = (uint32_t) pos_timer_read();
  return (t*POS_IN_A_TURN/countPerTour)%POS_IN_A_TURN;
  // return MIN((int)(pos_timer_read()*POS_IN_A_TURN/countPerTour), POS_IN_A_TURN);
  // return MIN((int)(TCNT3*POS_IN_A_TURN/countPerTour), POS_IN_A_TURN);
}
