
#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC / 16 / BAUD - 1

#include <avr/io.h>
#include <util/delay.h> // for _delay_ms()
//LE=PE5
//OE=PE4
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

void main(void)
{
    SPI_MasterInit();
    while (1)
    {

        PORTE &= ~_BV(PE4);
        SPI_MasterTransmit(8);
        SPI_MasterTransmit(8);
        PORTE |= _BV(PE5);
        PORTE &= ~_BV(PE5);
    }
}

void SPI_MasterInit(void)
{
    DDRE |= _BV(PE5);
    DDRE |= _BV(PE4);
    /* Set MOSI and SCK output, all others input */
    DDRB = (1 << DDB2) | (1 << DDB1);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
}