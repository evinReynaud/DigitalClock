#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "bluetooth.h"
#include "interface.h"
#include "clock.h"

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
    char data[256];
    bluetooth_fetch_data(data);
    if (strlen(data) == 0)
        return;
    if (data[0] == 'H')
    {
        hours = chartoi(data[2]) * 10 + chartoi(data[3]);
        minutes = chartoi(data[4]) * 10 + chartoi(data[5]);
        if (hours > 12)
        {
            hours = 12;
        }
        if (minutes > 59)
        {
            minutes = 59;
        }

        seconds = 0;
    }

    if (data[0] == 'I')
    {
        send_info();
    }

    //if (data[0] == 'M')
    //{
    //    mode = atoi(data[2]);
    // ajouter le code permettant d'affecter les valeurs
    //}
}
