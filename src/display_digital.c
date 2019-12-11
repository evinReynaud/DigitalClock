#include <stdio.h>

#include "clock.h"
#include "position.h"

#include "debug.h"

#include "display_digital.h"

#ifndef COUNTERCLOCKWISE
// clockwise

#else
// counterclockwise

#endif


void init_digital_display(uint16_t * display)
{
  (void) display;
}

// void compute_display_slow() {
//   h_pos = hour_to_pos(hours, minutes);
//   m_pos = minute_to_pos(minutes, seconds);
//   s_pos = seconds_to_pos(seconds);
//   for(int pos = 0; pos < POS_IN_A_TURN; pos++){
//     uint16_t leds = get_hands(pos, h_pos, m_pos, s_pos);
//     if(display[pos] != leds)
//       display[pos] = leds;
//   }
// }

void compute_digital_display(uint16_t * display)
{
  (void) display;
}
