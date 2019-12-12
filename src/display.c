#include <stdio.h>

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

  // display[0] = 0b1111000000000000;
  // display[POS_IN_A_TURN/4] = 0b0000111100000000;
  // display[POS_IN_A_TURN/2] = 0b0000000011110000;
  // display[3*POS_IN_A_TURN/4] = 0b0000000000001111;

  debug_show_array();
}

void (*compute[NB_MODES])(uint16_t * display) = {&compute_analog_display, &compute_digital_display};

void compute_display() {
  compute[mode](display);
  // debug_show_array();
}

void display_strip()
{
  leds_on(display[get_pos()]);

  // uint32_t pos = get_pos();
  // leds_on(display[pos]);
  // leds_on(LEDS_OFF);
  // char b[20];
  // sprintf(b, "%d\n", pos);
  // debug_printf(b);
}
