#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "display.h"
#include "position.h"

#include "debug.h"

#include "interface.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

int reset = 0;

void send_info()
{
  bluetooth_transmit("send I to display this screen\n");
  bluetooth_transmit("send H_hhmm to change hour\n");
  bluetooth_transmit("send M_n  with n=1,2 to change mode\n");
  bluetooth_transmit("send O_xxx to change the clock orientation (ex: O_-10)\n");
  bluetooth_transmit("send r for a soft restart\n");
  bluetooth_transmit("send R for a full restart\n");
}

void set_effethall_timer(char * data)
{
  char timer[17];
  strcpy(timer, data + 2);

  effethall_timer = atoi(timer);

  char b[64];
  sprintf(b, "Changed timer: %s -> %u\n", timer, effethall_timer);
  bluetooth_transmit(b);
}

void set_mode(char * data)
{
  int m = atoi(data+2) - 1;
  char b1[64];
  sprintf(b1, "mode %d\n", mode);
  debug_printf(b1);
  if (m >= ANALOG && m < NB_MODES) {
    debug_printf("A\n");
    mode = m;
    debug_printf("B\n");
    init_display();
    debug_printf("C\n");

    // sprintf(data, "Changed to mode %d\n", m+1);
    debug_printf("D\n");
    // bluetooth_transmit(data);
  }
}

void set_offset(char * data)
{
  if(data[2]=='r')
    offset=0;
  else {
    int m = -atoi(data+2);
    while(m<0)
      m+=POS_IN_A_TURN;
    offset = (offset + m) % POS_IN_A_TURN;
  }
}

void interface()
{
  if (!bluetooth_data_ready())
    return;

  char data[256];
  bluetooth_wait_for_data(data);
  if (strlen(data) == 0)
    return;
  switch(data[0]){
    case 'H':
    set_time(atoi(data + 2) / 100, atoi(data + 4), 0);
    bluetooth_transmit("hour changed\n");
    break;

    case 'I':
    case 'h':
    send_info();
    break;

    case 'r':
    reset = 1;
    break;

    case 'R':
    reset = 2;
    break;

    case 'd':
    set_effethall_timer(data);
    break;

    case 'M':
    set_mode(data);
    break;

    case 'O':
    set_offset(data);
    break;
  }
}
