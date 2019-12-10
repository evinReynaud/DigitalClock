#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "pos_timer.h"

void pos_timer_start()
{
  /* start timer clock */
  TCCR3B |= _BV(CS30)|_BV(CS32);
  //TCCR1B |= _BV(CS11); /* prescaler: 8 */
}

void pos_timer_stop()
{
  TCCR3B &= ~(_BV(CS30)|_BV(CS31)|_BV(CS32)); /* stop timer clock */
  ETIMSK &= ~_BV(TOIE3); /* disable interrupt */
  //TIFR |= _BV(TOV1); /* clear interrupt flag */    //  A revoir parce que j'ai des doutes
}

void pos_timer_init()
{
  /* normal mode */
  TCCR3A &= ~((_BV(WGM30)|_BV(WGM31)));
  TCCR3B &= ~((_BV(WGM33)|_BV(WGM32)));
  pos_timer_stop();
}

uint16_t TIM16_ReadTCNT3()
{
  uint16_t val;
  unsigned char sreg;
  /* Save global interrupt flag */
  sreg = SREG;
  /* Disable interrupts */
  //__disable_interrupt();
  cli();
  /* Read TCNTn into i */
  //countPerTour = TCNT3 - countPerTour + countI*valueMaxCount;
  val = TCNT3;
  /* Restore global interrupt flag */
  sei();
  SREG = sreg;

  return val;
}

inline uint16_t pos_timer_read(){
  return TIM16_ReadTCNT3();
}

void TIM16_WriteTCNT3(unsigned int i)
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

inline void pos_timer_write(uint16_t val){
  TIM16_WriteTCNT3(val);
}
