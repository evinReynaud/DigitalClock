// En-têtes fournies par AVR pour les registres
#include <avr/io.h>

#include "bluetooth.h"

void Bluetooth_Init(unsigned int ubrr)
{
  //Set baud rate
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Set frame format: 8data, 2stop bit
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

char Bluetooth_Receive_Char()
{
  // Wait for data to be received
  while (!(UCSR0A & (1 << RXC0)))
    ;
  // Get and return received data from buffer
  return UDR0;
}

void Bluetooth_Receive(char* buff)
{
  char c;
  do {
    c = Bluetooth_Receive_Char();
    *buff = c;
    buff++;
  } while (c != '\n');
  *buff = '\0';
}

void Bluetooth_Transmit_Char(char data)
{
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Put data into buffer, sends the data
  UDR0 = data;
}

void Bluetooth_Transmit(char* data)
{
  while(*data != '\0') {
    Bluetooth_Transmit_Char(*data++);
  }
}
