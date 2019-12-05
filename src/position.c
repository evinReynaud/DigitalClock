

#include "position.h"
volatile  uint16_t countPerTour = 1;
volatile int etat =0;
volatile int follow = 0;
void timer_init_postion(void)
{
    /* normal mode */
    TCCR3A &= ~((_BV(WGM30)|_BV(WGM31)));
    TCCR3B &= ~((_BV(WGM33)|_BV(WGM32)));
    timer_stop_position();
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



void TIM16_WriteTCNT3( unsigned int i )
{
  unsigned char sreg;
  /* Save global interrupt flag */
  sreg = SREG;
  /* Disable interrupts */
  cli();
  /* Set TCNTn to i */
  TCNT3 = i;
  /* Restore global interrupt flag */
  sei();
  SREG = sreg;
}

void TIM16_ReadTCNT3( void )
{
  unsigned char sreg;
  /* Save global interrupt flag */
  sreg = SREG;
  /* Disable interrupts */
  //__disable_interrupt();
  cli();
  /* Read TCNTn into i */
  //countPerTour = TCNT3 - countPerTour + countI*valueMaxCount;
  countPerTour = TCNT3;
  /* Restore global interrupt flag */
  sei();
  SREG = sreg;
}

void SPI_master_transmit(uint16_t data)
{
    char c1 = (char)(data >> 8);
    char c2 = (char)data;
    _delay_us(1);
    SPI_master_transmit_char(c1);
    SPI_master_transmit_char(c2);
    _delay_us(5);
    PORTE |= _BV(PE5);
    _delay_us(5);
    PORTE &= ~_BV(PE5);
    _delay_us(5);
}


int getPos(void)
{
    TIM16_ReadTCNT3();
    return (int)(TCNT3*POS_IN_A_TURN/countPerTour);

}


void timer_stop_position(void)
{
    TCCR3B &= ~(_BV(CS30)|_BV(CS31)|_BV(CS32)); /* stop timer clock */
    ETIMSK &= ~_BV(TOIE3); /* disable interrupt */
    //TIFR |= _BV(TOV1); /* clear interrupt flag */    //  A revoir parce que j'ai des doutes
}
