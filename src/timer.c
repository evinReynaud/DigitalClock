#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer_init(void)
{
    sei();
    /* fast pwm mode */
    TCCR1A |= (_BV(WGM10)|_BV(WGM11));
    TCCR1B |= (_BV(WGM13)|_BV(WGM12));
    timer_stop();
}

void timer_start(void)
{
    timer_init();
    //OCR1  = 1624 ; /* overflow in OCR1*8 clock cycles */
    OCR1AH = 0b00000110;
    OCR1AL = 0b01011000;
    TIMSK |= _BV(TOIE1); /* enable overflow interrupt */
    /* start timer clock */
    //TCCR1B &= ~(_BV(CS10)|_BV(CS11)|_BV(CS12));
    TCCR1B |= _BV(CS11); /* prescaler: 8 */
    time_count = 1000;
    tic = 0;
}

void timer_stop(void)
{
    TCCR1B &= ~(_BV(CS10)|_BV(CS11)|_BV(CS12)); /* stop timer clock */
    TIMSK &= ~_BV(TOIE1); /* disable interrupt */
    //TIFR |= _BV(TOV1); /* clear interrupt flag */    //  A revoir parce que j'ai des doutes
}

ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
{
    time_count -= 1;
    if(time_count == 0)
    {
       // Il s'est écoulé une seconde j'incrémente d'une seconde.
       time_count = 1000;
       tic = 1-tic;
    }
}
