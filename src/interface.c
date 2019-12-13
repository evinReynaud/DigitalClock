#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "config.h"
#include "display.h"
#include "display_digital.h"
#include "debug.h"
#include "interface.h"
#include "position.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

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
  bluetooth_transmit("send d_xx to change the delay for the hysterisis (d_8 is fine) \n");
  bluetooth_transmit("send O_xxx to change the clock orientation (ex: O_-10)\n");
  bluetooth_transmit("send O_r to reset orientation\n");

  //bluetooth_transmit("send r for a soft  restart\n");
  //bluetooth_transmit("send R for a complete restart\n");
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

uint8_t chartoi(char c)
{
  char stTemp[2];
  uint8_t ctoi;
  sprintf(stTemp, "%c", c);
  ctoi = atoi(stTemp);
  return ctoi;
}

void set_effethall_timer(char *data)
{
  char timer[17];
  strcpy(timer, data + 2);

  effethall_timer = atoi(timer);

  char b[64];
  sprintf(b, "Changed timer: %s -> %u\n", timer, effethall_timer);
  bluetooth_transmit(b);
}

void interface()
{
  if (bluetooth_data_ready())
  {
    char data[256];
    bluetooth_wait_for_data(data);
    if (strlen(data) == 0)
      return;

    if (data[0] == 'H')
    {
      set_time(chartoi(data[2]) * 10 + chartoi(data[3]), chartoi(data[4]) * 10 + chartoi(data[5]), 0);
      bluetooth_transmit("hour changed\n");
    }
    else if (data[0] == 'O')
    {
      set_offset(data);
    }

    else if (data[0] == 'I' || data[0] == 'h')
    {
      send_info();
    }

    else if (data[0] == 'r')
    {
      reset = 1;
    }

    else if (data[0] == 'R')
    {
      reset = 2;
    }
    else if (data[0] == 'd')
    {
      set_effethall_timer(data);
    }
    else if (data[0] == 'M' && data[2] == '1')
    {
      mode = ANALOG;
      char b[64];
      sprintf(b, "Changed mode: %d\n", mode);
      bluetooth_transmit(b);
      init_display();
    }
    else if (data[0] == 'M' && data[2] == '2')
    {
      mode = DIGITAL;
      char b[64];
      sprintf(b, "Changed mode: %d\n", mode);
      bluetooth_transmit(b);
    }
    else if (data[0] == 'M' && data[2] == '3')
    {
      mode = CUSTOM_DIGITAL;
      char b[64];
      sprintf(b, "Changed mode: %d\n", mode);
      bluetooth_transmit(b);
    }
    else if (data[0] == 'M' && data[2] == '4')
    {
      mode = LOVE;
      char b[64];
      sprintf(b, "Changed mode: %d\n", mode);
      bluetooth_transmit(b);
    }
    else if (data[0] == '1')
    {
      if (mode == CUSTOM_DIGITAL && strlen(data) < 15)
      {
        strcpy(line1, data + 2);
      }
    }
    else if (data[0] == '2')
    {
      if (mode == CUSTOM_DIGITAL && strlen(data) < 15)
      {
        strcpy(line2, data + 2);
      }
    }
  }
}
