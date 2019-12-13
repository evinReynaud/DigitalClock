#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "bluetooth.h"

#define debug_printf(B) bluetooth_transmit(B)

void debug_wait_input();

#endif
