
#include <stdio.h>

#include "leds.h"
#include "timer.h"
#include "bluetooth.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "effethall.h"
#include "spi.h"
#include "position.h"
#include <util/delay.h>

#define valueMaxCount  0xFFFF
#define prescaler 1024
#define fos 13000000
volatile  uint16_t countPerTour = 0;
volatile int countI = 0;
volatile int countIe = 0;
volatile int etat =0;
volatile int follow = 0;
volatile int time = 0;

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
  countI = 0;
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



void test_effethall()
{
  // Change pin 0 on bus D to an input by changing bit 0 to zero
  DDRD &= ~(1 << PIN0);
  // Allow external interrupt 0
  EIMSK |= (1 << INT0);
  // Allow global interrupts
  sei();
  SPI_master_init();
  //uint16_t d = 0b1111110000110001;
  while (TRUE)
  {

    SPI_master_transmit(0b0000000000000000);
    if (etat == 1)
    {
      //while(TCNT3 < (countPerTour + (int)countPerTour/100)){}
      //TIM16_ReadTCNT3();
      //bluetooth_transmit_uint16(countPerTour);                                                                                                                                                                                           fbv
      if(follow==0)
      {
        follow = 1;
        //SPI_master_transmit(0b1111111111111111);
        TIM16_ReadTCNT3();
        bluetooth_transmit_uint16(countPerTour);
        time = countPerTour;
        TIM16_WriteTCNT3(0);
        bluetooth_ln();

      }



      if( TCNT3 > time + 120)
      {
        etat = 0;
        follow = 0;
      }
      //bluetooth_transmit_uint16(countIe);
      //countIe =0;
      //bluetooth_ln();
      //_delay_ms((int)countPerTour/8);
      // On met notre flag à 1, pour signaler que notre Bp à été appuyé
     }

    //bluetooth_transmit_uint16(TCNT3);
    //bluetooth_ln();
  }                      // Nous arrivons à la parenthèse de la boucle infini, donc on repart au début et ainsi de suite .
}


ISR(INT0_vect)
{
  //TIM16_ReadTCNT3();
  etat = 1;
  countIe++;
}



ISR(TIMER3_OVF_vect) /* timer 1 interrupt service routine */
{
  countI++;
  //bluetooth_transmit_uint16(countI);

}

void main()
{
  timer_init_postion();
  timer_start_position();
  //effethall_init();
  bluetooth_init();
  //bluetooth_transmit_int32(countPerTour);
  test_effethall();
}
