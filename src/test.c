#include <stdlib.h>

#include "bluetooth.h"

#include "test.h"

void test_init()
{
  hours = 0;
  minutes = 0;
  seconds = 0;
  arc = 0;
}

int get_arc_min()
{
  return arc;
}

void get_values()
{
  char b[256];
  bluetooth_wait_for_data(b);
  char h[3] = {b[0], b[1], '\n'};
  char m[3] = {b[3], b[4], '\n'};
  char s[3] = {b[6], b[7], '\n'};
  char a[6] = {b[9], b[10], b[11], b[12], b[13], '\n'};

  hours = atoi(h);
  minutes = atoi(m);
  seconds = atoi(s);
  arc = atoi(a);
}

void print(char* str)
{
  bluetooth_transmit(str);
}
