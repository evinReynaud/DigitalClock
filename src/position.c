#include <stdint.h>

#include "config.h"
#include "pos_timer.h"
#include "hall_effect.h"

#include "position.h"

int offset = 0;

void position_init()
{
  pos_timer_init();
  hall_effect_init();
  pos_timer_start();
}

uint32_t get_pos()
{
  uint32_t t = pos_timer_read();
  return (offset + (t * POS_IN_A_TURN / countPerTour)) % POS_IN_A_TURN;
}

inline void check_position()
{
  hall_effect_enable_interruption();
}
