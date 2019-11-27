#include "usart.h"
#include "bluetooth.h"
#include "interface.h"

void send_info()
{
    char data[256];
    sprintf(data, "send H to change hour\n");
    bluetooth_transmit(data);
    sprintf(data, "send M to change mode\n");
    bluetooth_transmit(data);
    sprintf(data, "send C to specify the clockwise\n"); // direction de l'aiguille
    bluetooth_transmit(data);
}

void interface()
{
    if (bluetooth_receive_char() == 'H')
    {
        char data[256];
        sprintf(data, "waiting for hour format: hhmmss\n");
        bluetooth_transmit(data);
        // ajouter le code permettant d'affecter les valeurs
    }

    if (bluetooth_receive_char() == 'M')
    {
        char data[256];
        sprintf(data, "waiting for a mode: 1, 2 or 3\n");
        bluetooth_transmit(data);
        // ajouter le code permettant d'affecter les valeurs
    }

    if (bluetooth_receive_char() == 'C')
    {
        char data[256];
        sprintf(data, "waiting for clockwise: 0 or 1\n"); // pour que la personne puisse dire si l'aiguille tourne dans le sens des aiguilles d'une montre ou non
        bluetooth_transmit(data);
        // ajouter le code permettant d'affecter les valeurs
    }
}