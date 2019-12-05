#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define TRUE 1
#define FALSE 0

void bluetooth_init();
void bluetooth_wait_for_data(char *buff);
void bluetooth_transmit(char *data);
void bluetooth_transmit_char(char data);

#endif
