#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

void Bluetooth_Init(unsigned int ubrr);

unsigned char Bluetooth_Receive(void);

void Bluetooth_Transmit(unsigned char data);

#endif
