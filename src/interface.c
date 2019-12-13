#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "display.h"

#include "debug.h"
#include "interface.h"
#include "position.h"

#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

volatile int data_received = 0;
volatile int degre = 0;

int reset = 0;

void send_info()
{
  bluetooth_transmit("send H_hhmm to change hour\n");
  bluetooth_transmit("send M_n  with n=1,2 to change mode\n");
  bluetooth_transmit("send D_n  with n=100 degre to change degre or D_r to reset \n");

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

    else if (data[0] == 'd')
    {
      char timer[17];
      strcpy(timer, data+2);

      effethall_timer = atoi(timer);

      char b[64];
      sprintf(b, "Changed timer: %s -> %u\n", timer, effethall_timer);
      debug_printf(b);
    }
    else if (data[0] == 'M')
    {
      int m = chartoi(data[2]) - 1;
      if(m >= ANALOG && m < NB_MODES){
        mode = m;
        char b[64];
        sprintf(b, "Changed mode: %d\n", mode);
        debug_printf(b);
        init_display();
      }
       //ajouter le code permettant d'affecter les valeurs
    }
    else if (data[0] == 'D')
    {
      if(data[2]=='r')
      {
        degre=0;
      }
      else
      { 
        int m = -atoi(data+2);
        while(m<0)
        {
          m+=POS_IN_A_TURN;
        }
        degre += m;
        degre %= POS_IN_A_TURN;
      }

      // if(len>2)
      // {
      //   if(data[2]=='-' && len>3)
      //   {
      //     for(int i = 3;i<len;i++)
      //     {
      //       m+=chartoi(data[i])*pow(10,(len-i-1));
      //     }
      //     m *=-1;
      //   }
      //   else if(data[2]=='r')
      //   {
      //     degre=0;
      //   }
      //   else
      //   {
      //     for(int i =2;i<len;i++)
      //     {
      //       m+=chartoi(data[i])*pow(10,(len-i-1));
      //     }
      //   }
    }
  }
    data_received = FALSE;
}
