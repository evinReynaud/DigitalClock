#include <stdlib.h>

#include "bluetooth.h"

#include "test.h"

int arc = 0;

int get_arc_min()
{
  return arc;
}

void print(char* str)
{
  bluetooth_transmit(str);
}
