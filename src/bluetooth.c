#include "usart.h"
#include "bluetooth.h"

void bluetooth_init()
{
  USART_init(MYUBRR);
}

inline char bluetooth_receive_char()
{
  return USART_receive();
}

void bluetooth_transmit_char(char data)
{
  USART_transmit(data);
}

void bluetooth_wait_for_data(char *buff)
{
  char c;
  do
  {
    c = bluetooth_receive_char();
    *buff = c;
    buff++;
  } while (c != '\n');
  *buff = '\0';
}

void bluetooth_transmit(char *data)
{
  while (*data != '\0')
  {
    bluetooth_transmit_char(*data++);
  }
}

inline int bluetooth_data_ready()
{
  return USART_data_ready();
}


void bluetooth_transmit_uint16(uint32_t i) {
  char buffer[16];
  sprintf(buffer, "%lu", i);
  bluetooth_transmit(buffer);
}


void bluetooth_ln() {
  bluetooth_transmit_char('\r');
  bluetooth_transmit_char('\n');
}
