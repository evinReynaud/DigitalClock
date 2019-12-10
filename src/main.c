
#include "bluetooth.h"
#include "position.h"

int main()
{
  position_init();
  bluetooth_init();

  while (1)
  {
    bluetooth_transmit_uint16(get_pos());
    bluetooth_ln();
  }
  return 0;
}
