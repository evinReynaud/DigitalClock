#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "config.h"
#include "pos_timer.h"
#include "effethall.h"

#include "position.h"

uint16_t countPerTour = 1;

void position_init()
{
  pos_timer_init();
  effethall_init();
  pos_timer_start();
}

void func(){
  countPerTour = pos_timer_read();
  //bluetooth_transmit_uint16(countPerTour);
  pos_timer_write(0);
  //bluetooth_ln();
}

int get_pos()
{
  check_effethall(&func, TCNT3);
  countPerTour = pos_timer_read();
  return (int)(TCNT3*POS_IN_A_TURN/countPerTour);
}
