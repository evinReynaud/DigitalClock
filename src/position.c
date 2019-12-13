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

#include "interface.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

void position_init()
{
  pos_timer_init();
  effethall_init();
  pos_timer_start();
}

//void move(int degre)

uint32_t get_pos()
{
  uint32_t t = (uint32_t) pos_timer_read();
  return (degre + (t*POS_IN_A_TURN/countPerTour))%POS_IN_A_TURN;
}

inline void check_position()
{
  effethall_enable_interruption();
}
