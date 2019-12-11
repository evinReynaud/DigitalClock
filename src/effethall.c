#include <avr/interrupt.h>
#include <avr/io.h>

#include "pos_timer.h"

#include <stdio.h>
#include "debug.h"

#include "effethall.h"

volatile uint16_t countPerTour = 1;


ISR(INT0_vect)
{

  countPerTour = pos_timer_read();
  pos_timer_write(1);
  EIMSK &= ~(1 << INT0);

  //pos_timer_write(1);
  // char b[8];
  // sprintf(b, "%d\n", countPerTour);
  // debug_printf(b);
}

void effethall_init()
{
  sei();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);

  // Detect falling edge
  EICRA |= (1 << ISC01);

  // Allow external interrupt 0
  EIMSK |= (1 << INT0);

  countPerTour = 1;
}
