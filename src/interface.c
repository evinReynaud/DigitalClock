#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"

#include "debug.h"

#include "interface.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

volatile int data_received = 0;
int reset = 0;

void send_info()
{
  char data[256];
  sprintf(data, "send H_hhmm to change hour\n");
  bluetooth_transmit(data);
  //sprintf(data, "send M_n  with n=1,2,3 to change mode\n");
  //bluetooth_transmit(data);
}

uint8_t chartoi(char c)
{
  char stTemp[2];
  uint8_t ctoi;
  sprintf(stTemp, "%c", c);
  ctoi = atoi(stTemp);
  return ctoi;
}

void interface()
{
  if (bluetooth_data_ready())
  {
    char data[256];
    bluetooth_wait_for_data(data);
    if (strlen(data) == 0)
    return;

    // bluetooth_transmit(data);
    // char b[8];
    // sprintf(b, "\n%d\n", strlen(data));
    // debug_printf(b);

    if (data[0] == 'H')
    {
      hours = MIN(chartoi(data[2]) * 10 + chartoi(data[3]), 23);
      minutes = MIN(chartoi(data[4]) * 10 + chartoi(data[5]) - 1, 59);

      seconds = 0;
      sprintf(data, ".. Hour changed ..\n");
      bluetooth_transmit(data);

      // char b[64];
      // sprintf(b, "  %d:%d:%u\n", hours, minutes, seconds);
      // debug_printf(b);
    }

    else if (data[0] == 'I')
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

    //if (data[0] == 'M')
    //{
    //    mode = atoi(data[2]);
    // ajouter le code permettant d'affecter les valeurs
    //}

    data_received = FALSE;
  }
}
