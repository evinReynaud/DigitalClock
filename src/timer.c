#include <avr/io.h>
#include <avr/interrupt.h>

static void timer_stop(void)
{
    TCCR1B &= ~(_BV(CS10)|_BV(CS11)|_BV(CS12)); /* stop timer clock */
    TIMSK1 &= ~_BV(TOIE1); /* disable interrupt */
    TIFR1 |= _BV(TOV1); /* clear interrupt flag */    //  A revoir parce que j'ai des doutes
}

static int timeCount=1000;

static void timer_init(void)
{
    /* fast pwm mode */
    TCCR1A |= (_BV(WGM10)|_BV(WGM11));
    TCCR1B |= (_BV(WGM13)|_BV(WGM12));
    timer_stop();
}


static void timer_start(void)
{
    timer_init();
    //OCR1  = 1625 ; /* overflow in OCR1*8 clock cycles */
    OCR1H = 0b00000110
    OCR1L = 0b01011001
    TIMSK1 |= _BV(TOIE1); /* enable overflow interrupt */
    /* start timer clock */
    //TCCR1B &= ~(_BV(CS10)|_BV(CS11)|_BV(CS12));
    TCCR1B |= _BV(CS10); /* prescaler: 8 */
}

ISR(TIMER1_OVF_vect) /* timer 1 interrupt service routine */
{
    timeCount -=1;
    if(timeCount==0)
    {
       // Il c'est écouler une seconde j'incrémente de une seconde.
    }
}

void main(){
  //spi_init();

}
