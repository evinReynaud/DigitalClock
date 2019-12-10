

#include "position.h"

#include "effethall.h"

int main()
{
  timer_init_postion();
  timer_start_position();
  bluetooth_init();
  effethall_init();
  SPI_master_init();

  while (1)
  {
    bluetooth_transmit_uint16(getPos());
    bluetooth_ln();
    check_effethall();
  }
  return 0;
}
