#include <avr/io.h>

//LE=PE5
//OE=PE4

void SPI_MasterInit(void)
{
    DDRE |= _BV(PE4);
    DDRE &= ~_BV(PE5);
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