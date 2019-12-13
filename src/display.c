#include <stdio.h>

#include "config.h"
#include "leds.h"
#include "clock.h"
#include "position.h"

#include "display_analog.h"
#include "display_digital.h"

#include "debug.h"

#include "display.h"

enum display_mode mode = ANALOG;

uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

#ifndef COUNTERCLOCKWISE
// clockwise

#else
// counterclockwise

#endif

void debug_show_array(){
  char b[16];
  for(int pos = 0; pos < POS_IN_A_TURN; pos++){
    if(display[pos] != 0){
      sprintf(b, "%03d: %x\n", pos, display[pos]);
      debug_printf(b);
    }
  }
}

inline void init_display_array(){
  for(int pos = 0; pos < POS_IN_A_TURN; pos++){
    display[pos] = LEDS_OFF;
  }
}

void (*init[NB_MODES])(uint16_t * display) = {&init_analog_display, &init_digital_display};

void init_display(){
  init_display_array();
  init[mode](display);
}

void (*compute[NB_MODES])(uint16_t * display) = {&compute_analog_display, &compute_digital_display};

void compute_display() {
  compute[mode](display);
}

void display_strip()
{
  leds_on(display[get_pos()]);
}
