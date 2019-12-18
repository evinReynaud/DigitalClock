#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "pos_timer.h"
#include "leds.h"

#ifdef BENCHMARK
#include "benchmark.h"
#include "bluetooth.h"
#endif

#include "hall_effect.h"

volatile uint16_t countPerTour = 1;

uint16_t hall_effect_timer = 0;

#ifdef DEBUG_HALL
volatile int c = 0;
#endif

ISR(INT0_vect)
{
  #ifdef BENCHMARK
  uint16_t begining, end;

  pos_timer_write(1);
  pos_timer_start();
  begining = pos_timer_read();

  // We invert the operations to have the most accurate measure possible while doing the same operations
  pos_timer_write(1);
  countPerTour = pos_timer_read();

  end = pos_timer_read();
  pos_timer_stop();
  timeInInterrup += end-begining;

  #else
  EIMSK &= ~(1 << INT0);
  countPerTour = pos_timer_read();
  pos_timer_write(1);
  #ifdef DEBUG_HALL
  leds_on(LEDS_ON);
  leds_on(LEDS_OFF);
  #endif
  #endif
}

void hall_effect_init()
{
  cli();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);

  // Detect falling edge
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
  sei();

  countPerTour = 1;
  hall_effect_timer = 0;
  #ifdef BENCHMARK
  EIFR |= (1 << INTF0);
  #else
  #endif
}

inline void hall_effect_enable_interruption()
{
  if(TCNT3 > hall_effect_timer) {
    EIFR |= (1 << INTF0);
    EIMSK |= (1 << INT0);
  }

  #ifdef DEBUG_HALL
  if (TCNT3 > 20000)
    c = 0;
  #endif
}
