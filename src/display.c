#include <stdio.h>

#include "config.h"
#include "leds.h"
#include "clock.h"
#include "position.h"

#include "display_analog.h"
#include "display_digital.h"

#include "display.h"

enum display_mode mode = ANALOG;

uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

inline void init_display_array(){
  for(int pos = 0; pos < POS_IN_A_TURN; pos++){
    display[pos] = LEDS_OFF;
  }
}

void (*init[NB_MODES])(uint16_t * display) = {&init_analog_display, &init_digital_display, &init_digital_display, &init_digital_display};

inline void init_display(){
  init_display_array();
  init[mode](display);
}

void (*compute[NB_MODES])(uint16_t * display) = {&compute_analog_display, &compute_digital_display, &compute_custom_display, &compute_love_display};

inline void compute_display() {
  compute[mode](display);
}

inline void display_strip()
{
  leds_on(display[get_pos()]);
}
