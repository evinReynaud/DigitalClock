#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"

#include "interface.h"

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

void interface_interrupt_init(void)
{
    sei();
    UCSR0B |= _BV(RXCIE0);
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
    if (data_received)
    {
        char data[256];
        bluetooth_wait_for_data(data);
        if (strlen(data) == 0)
            return;

        //bluetooth_transmit(data);

        if (data[0] == 'H')
        {
            hours = chartoi(data[2]) * 10 + chartoi(data[3]);
            minutes = chartoi(data[4]) * 10 + chartoi(data[5]) - 1;
            if (hours > 23)
            {
                hours = 23;
            }
            if (minutes > 59)
            {
                minutes = 59;
            }

            seconds = 0;
            sprintf(data, ".. Hour changed ..\n");
            bluetooth_transmit(data);
        }

        if (data[0] == 'I')
        {
            send_info();
        }

        if (data[0] == 'r')
        {
          reset = 1;
        }

        if (data[0] == 'R')
        {
          reset = 2;
        }

        if (data[0] == 'F')
        {
          force_hall = 1;
        }

        //if (data[0] == 'M')
        //{
        //    mode = atoi(data[2]);
        // ajouter le code permettant d'affecter les valeurs
        //}

        data_received = FALSE;
    }
}

ISR(USART0_RX_vect) /* timer 1 interrupt service routine */
{
    if (!data_received)
    {
        data_received = TRUE;
    }
}
