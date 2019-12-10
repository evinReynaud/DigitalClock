#include <avr/interrupt.h>
#include <avr/io.h>

#include "effethall.h"

volatile int etat = 0;
int follow = 0;

ISR(INT0_vect)
{
  etat = 1;
}

void effethall_init()
{
  sei();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);
  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
}

void check_effethall(void (*treatment)(), uint16_t timer)
{
  if(etat == 1)
  {
    if(follow == 0)
    {
      follow = 1;
      (*treatment)();
    }
    else if(timer > 10)
    {
      etat = 0;
      follow = 0;
    }
  }
}
