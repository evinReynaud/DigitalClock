#include <avr/io.h>

#include "usart.h"

void USART_init(unsigned int ubrr)
{
  //Set baud rate
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char) ubrr;
  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Set frame format: 8data, 2stop bit
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

char USART_receive()
{
  // Wait for data to be received
  while (!(UCSR0A & (1 << RXC0)));
  // Get and return received data from buffer
  return UDR0;
}

char USART_fetch()
{
  // Wait for data to be received
  if (!(UCSR0A & (1 << RXC0))){
    // Get and return received data from buffer
    return UDR0;
  }
  return '\n';
}

void USART_transmit(char data)
{
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Put data into buffer, sends the data
  UDR0 = data;
}
