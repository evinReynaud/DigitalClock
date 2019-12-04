#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer_init(void)
{
    sei();
    /* fast pwm mode = on s'arrete quand on arrive à la valeur que l'on a fixé */
    TCCR1A |= (_BV(WGM10) | _BV(WGM11));
    TCCR1B |= (_BV(WGM13) | _BV(WGM12));
    timer_stop(); // on veut pas qu'il commence à compter tout de suite
}

void timer_start(void)
{
    timer_init();
    //OCR1  = 1624 ; /* overflow in OCR1*8 clock cycles */
    OCR1AH = 0b00000110; // on a 2* 8 bits car on est à 16 bits avec le timer 1
    OCR1AL = 0b01011001;
    TIMSK |= _BV(TOIE1); /* enable overflow interrupt pour le timer 1  */
    TCCR1B |= _BV(CS11); /* prescaler: 8 */
    time_count = 1000;   // on a une interruption toutes les ms donc on a besoin de 1000 interruptions pour avoir 1s
    seconds = 0;
}

void timer_stop(void)
{
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); /* stop timer clock */
    TIMSK &= ~_BV(TOIE1);                           /* disable interrupt */
}

ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
{
    time_count -= 1;
    if (time_count == 0)
    {
        // Il s'est écoulé une seconde j'incrémente d'une seconde.
        time_count = 1000;
        seconds = (seconds + 1) % 60;
    }
}