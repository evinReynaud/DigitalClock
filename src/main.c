
#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "effethall.h"
#include "spi.h"
void main()
{
  leds_init();
  timer_init();
  bluetooth_init();
  timer_start();

  leds_on(0xffff);
  while(1) {
    if(tic == 1) {
      leds_on(0);
    } else {
      leds_on(0xffff);
    }
  }
}



ISR(INT0_vect)
{
  SPI_MasterTransmit(0b1000000000000000);
}

void test_effethall()
{

  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);

  // Allow external interrupt 0
  EIMSK |= (1 << INT0);

  // Allow global interrupts
  sei();
  SPI_MasterInit();

  while (TRUE)
  {
    //SPI_MasterTransmit(0b1111110000110001); // the last bit is the led that is the closest of the center
  }
}
