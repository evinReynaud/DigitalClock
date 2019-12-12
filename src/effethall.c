#include <avr/interrupt.h>
#include <avr/io.h>

#include "pos_timer.h"

#include <stdio.h>
#include "debug.h"
#include "leds.h"

#include "effethall.h"

volatile uint16_t countPerTour = 1;

uint16_t effethall_timer = 100;

#ifdef DEBUG_HALL
volatile int c = 0;
#endif

ISR(INT0_vect)
{
  EIMSK &= ~(1 << INT0);
  if(TCNT3 > effethall_timer)
  {
    countPerTour = pos_timer_read();
    pos_timer_write(1);
    // char b[8];
    // sprintf(b, "%d\n", countPerTour);
    // debug_printf(b);
    #ifdef DEBUG_HALL
    leds_on(LEDS_ON);
    leds_on(LEDS_OFF);

    char b[8];
    sprintf(b, "%d\n", c++);
    debug_printf(b);
    #endif
  }
}

void effethall_init()
{
  cli();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);

  // Detect falling edge
  EICRA |=  (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
  sei();

  countPerTour = 1;
  effethall_timer = 100;
}

inline void effethall_enable_interruption()
{
  if(TCNT3 > effethall_timer)
  {
    // EIFR &= ~(1 << INTF0);
    EIFR |= (1 << INTF0);
    EIMSK |= (1 << INT0);
  }

  #ifdef DEBUG_HALL
  if(TCNT3 > 20000)
    c = 0;
  #endif
}
