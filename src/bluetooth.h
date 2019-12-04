#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define TRUE 1
#define FALSE 0

void bluetooth_init();

void bluetooth_wait_for_data(char* buff);

void bluetooth_fetch_data(char* buff);

void bluetooth_transmit(char *data);

#endif
