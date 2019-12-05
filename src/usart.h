#ifndef __USART_H__
#define __USART_H__

#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC / 16 / BAUD - 1

void USART_init(unsigned int ubrr);

char USART_receive();

char USART_receive_interrupt();

char USART_fetch();

void USART_transmit(char data);

#endif
