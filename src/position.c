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

int force_hall = 0;

inline int abs(int x) {
  return (x >= 0) ? x : -x;
}

uint16_t countPerTour = 1;

void position_init()
{
  pos_timer_init();
  effethall_init();
  pos_timer_start();
}

void func(){
  uint16_t t = pos_timer_read();
  pos_timer_write(1);
  if(t > countPerTour/100 || force_hall){
    countPerTour = t;
    force_hall = 0;
  }
  char b[20];
  sprintf(b, "%u\n", countPerTour);
  debug_printf(b);
}

inline void check_pos(){
  check_effethall(&func, TCNT3);
}

int get_pos()
{
  // char b[20];
  // sprintf(b, "%u, %u\n", pos_timer_read(), countPerTour);
  // debug_printf(b);
  // return (int)(pos_timer_read()-countPerTour);
  return (int)(pos_timer_read()*POS_IN_A_TURN/countPerTour);
  // return MIN((int)(pos_timer_read()*POS_IN_A_TURN/countPerTour), POS_IN_A_TURN);
  // return MIN((int)(TCNT3*POS_IN_A_TURN/countPerTour), POS_IN_A_TURN);
}
