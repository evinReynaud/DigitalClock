#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void SPI_master_init()
{
  DDRE = (1 << DDE5) | (1 << DDE4);
  /* Set SS, MOSI and SCK output, all others input */
  DDRB = (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
  PORTE &= ~_BV(PE4);
  PORTE &= ~_BV(PE5);
}

void SPI_master_transmit_char(char cData)
{
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)));
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

// end of communication
void SPI_master_EOC()
{
  PORTE |= _BV(PE5);
  _delay_us(0.05); // min 20 ns
  PORTE &= ~_BV(PE5);
}
