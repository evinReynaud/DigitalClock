#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

extern int reset;

void interface_interrupt_init(void);
void send_info();
uint8_t chartoi(char c);
void interface();

#endif
