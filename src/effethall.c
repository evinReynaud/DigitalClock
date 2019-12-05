//#include "spi.h"
#include "effethall.h"
#include "position.h"

ISR(INT0_vect)
{
  etat = 1;
}

// ISR(TIMER3_OVF_vect) /* timer 1 interrupt service routine */
// {
// }

void effethall_init()
{
  sei();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);
  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
}

void check_effet_hall() {
  // bluetooth_transmit_uint16(getPos());
  // bluetooth_ln();
  if( etat == 1)
  {
    if(follow == 0)
    {
      follow = 1;
      TIM16_ReadTCNT3();
      //bluetooth_transmit_uint16(countPerTour);
      TIM16_WriteTCNT3(0);
      //bluetooth_ln();
    }
    if( TCNT3 > 100)
    {
      etat = 0;
      follow = 0;
    }
  }
}
