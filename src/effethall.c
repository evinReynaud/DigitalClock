#include <avr/interrupt.h>
#include <avr/io.h>

#include <stdio.h>
#include "debug.h"
#include "leds.h"

#include "pos_timer.h"

#include "effethall.h"

// volatile int etat = 0;
volatile uint16_t countPerTour = 1;

volatile int force_hall = 0;

ISR(INT0_vect)
{
  uint16_t t = pos_timer_read();
  pos_timer_write(1);
  countPerTour = t;
  force_hall = 0;

  // Disable this interruption
  EIMSK &= ~(1 << INT0);

  // uint16_t t = pos_timer_read();
  // pos_timer_write(1);
  // leds_on(0xffff);
  // countPerTour = t;
  // force_hall = 0;
  // leds_on(0);
  // char b[20];
  // sprintf(b, "%u\n", countPerTour);
  // debug_printf(b);

}

void effethall_init()
{
  sei();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);
  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
}

inline void check_effethall()
{
  if(TCNT3 > 50)
  {
    // Enable the interruption
    EIMSK |= (1 << INT0);
  }
}

// void check_effethall(void (*treatment)(), uint16_t timer)
// {
//   if(etat == 1)
//   {
//     if(follow == 0)
//     {
//       follow = 1;
//       (*treatment)();
//     }
//     else if(timer > 10)
//     {
//       etat = 0;
//       follow = 0;
//     }
//   }
// }
