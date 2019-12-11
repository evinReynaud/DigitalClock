#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define TRUE 1
#define FALSE 0
#include <stdint.h>
#include <stdio.h>

void bluetooth_init();

void bluetooth_wait_for_data(char *buff);

void bluetooth_transmit(char *data);

void bluetooth_transmit_char(char data);

int bluetooth_data_ready();

void bluetooth_transmit_uint16(uint32_t i);
void bluetooth_ln() ;

#endif
