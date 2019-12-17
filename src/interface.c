#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "display.h"
#include "display_digital.h"
#include "position.h"

#include "interface.h"

int reset = 0;

void send_info()
{
  bluetooth_transmit("send H_hhmm to change hour\n");
  bluetooth_transmit("send M_n  with n=1,2,3 to change mode\n");
  bluetooth_transmit("Mode 1: clock\n");
  bluetooth_transmit("Mode 2: clock digital\n");
  bluetooth_transmit("Mode 3: custom display\n");
  bluetooth_transmit("Mode 4: gif love\n");
  bluetooth_transmit("in mode 3 send 1_text to change first text\n");
  bluetooth_transmit("in mode 3 send 2_text to change second text\n");
  bluetooth_transmit("send O_xxx to change the clock orientation (ex: O_-10)\n");
  bluetooth_transmit("send O_r to reset orientation\n");
  bluetooth_transmit("send d_xx to change the delay for the hysterisis (d_8 is fine) \n");
  bluetooth_transmit("send R to restart the clock\n");
}

void set_effethall_timer(char * data)
{
  char timer[17];
  strcpy(timer, data + 2);

  effethall_timer = atoi(timer);

  char b[64];
  sprintf(b, "Changed timer to %u\n", effethall_timer);
  bluetooth_transmit(b);
}

void set_mode(char * data)
{
  int m = atoi(data+2) - 1;
  if (m >= ANALOG && m < NB_MODES) {
    mode = m;
    init_display();
    sprintf(data, "Changed to mode %d\n", m+1);
    bluetooth_transmit(data);
  }
}

void set_offset(char *data)
{
  if (data[2] == 'r')
    offset = 0;
  else
  {
    int m = -atoi(data + 2);
    while (m < 0)
      m += POS_IN_A_TURN;
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

    case 'O':
    set_offset(data);
    break;

    case 'I':
    case 'h':
    send_info();
    break;

    case 'R':
    case 'r':
    reset = 1;
    break;

    case 'd':
    set_effethall_timer(data);
    break;

    case 'M':
    set_mode(data);
    break;

    case '1':
    if (mode == CUSTOM_DIGITAL && strlen(data) < 15)
    {
      strcpy(line1, data + 2);
    }
    break;

    case '2':
    if (mode == CUSTOM_DIGITAL && strlen(data) < 15)
    {
      strcpy(line2, data + 2);
    }
    break;
  }
}
