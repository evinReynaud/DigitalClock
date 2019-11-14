#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC / 16 / BAUD - 1
#define TRUE 1
#define FALSE 0

void Bluetooth_Init(unsigned int ubrr);

void Bluetooth_Receive(char* buff);

char Bluetooth_Receive_Char();

void Bluetooth_Transmit(char* data);

void Bluetooth_Transmit_Char(char data);

#endif
