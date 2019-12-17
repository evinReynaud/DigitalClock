
#ifdef BENCHMARK
#include "benchmark.h"
#include "bluetooth.h"
#define prescale 1024
#define foscms  13000
#endif


#include <avr/interrupt.h>
#include <avr/io.h>
#include "pos_timer.h"
#include <stdio.h>
#include "debug.h"
#include "leds.h"
#include "effethall.h"

volatile uint16_t countPerTour = 1;

uint16_t effethall_timer = 0;

#ifdef DEBUG_HALL
volatile int c = 0;
#endif

ISR(INT0_vect)
{

  #ifdef BENCHMARK
  uint16_t debut, fin;
  debut = pos_timer_read();
  EIMSK &= ~(1 << INT0);
  countPerTour = pos_timer_read();
  pos_timer_write(1);
  #ifdef DEBUG_HALL
  leds_on(LEDS_ON);
  leds_on(LEDS_OFF);
  #endif
  fin=pos_timer_read();
  pos_timer_stop();
  timeInInterrup = (countPerTour-debut+fin);
  char b[1000];
  sprintf(b,"analog time %lf\n",timeInInterrup);
  bluetooth_transmit(b);


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

void effethall_init()
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
  effethall_timer = 0;
}

inline void effethall_enable_interruption()
{
  if (TCNT3 > effethall_timer)
  {
    // EIFR &= ~(1 << INTF0);
    EIFR |= (1 << INTF0);
    EIMSK |= (1 << INT0);
  }

  #ifdef DEBUG_HALL
  if (TCNT3 > 20000)
    c = 0;
  #endif

}
