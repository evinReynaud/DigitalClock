

#include "position.h"



ISR(INT0_vect)
{
  etat = 1;
}



ISR(TIMER3_OVF_vect) /* timer 1 interrupt service routine */
{
}

void main()
{
  timer_init_postion();
  timer_start_position();
  bluetooth_init();
  effethall_init();
  SPI_master_init();
  while (TRUE)
  {
    bluetooth_transmit_uint16(getPos());
    bluetooth_ln();
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
}
