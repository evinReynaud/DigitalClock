#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "effethall.h"
#include "spi.h"




void timer_init_postion(void)
{
    /* normal mode */
    TCCR3A &= ~((_BV(WGM30)|_BV(WGM31)));
    TCCR3B &= ~((_BV(WGM33)|_BV(WGM32)));
    timer_stop();
}

void timer_start_position(void)
{

    timer_init_postion();
    sei();

    //OCR3  = 0xffffffffffffffff ; /* overflow in clock cycles */;
    ETIMSK |= _BV(TOIE3); /* enable overflow interrupt */
    /* start timer clock */
    TCCR3B |= _BV(CS30)|_BV(CS32);
    //TCCR1B |= _BV(CS11); /* prescaler: 8 */
}




void effethall_init()
{

  sei();
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);
  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
}

void timer_stop_position(void)
{
    TCCR3B &= ~(_BV(CS30)|_BV(CS31)|_BV(CS32)); /* stop timer clock */
    ETIMSK &= ~_BV(TOIE3); /* disable interrupt */
    //TIFR |= _BV(TOV1); /* clear interrupt flag */    //  A revoir parce que j'ai des doutes
}
