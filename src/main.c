
#include "bluetooth.h"
#include "position.h"

#include "debug.h"

int main()
{
  bluetooth_init();
  position_init();

  debug_printf("Init done\n");
  debug_wait_input();

  while (1)
  {
    bluetooth_transmit_uint16(get_pos());
    bluetooth_ln();
  }
  return 0;
}
