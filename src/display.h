#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

extern enum display_mode { ANALOG,
                           DIGITAL,
                           CUSTOM_DIGITAL,
                           LOVE,
                           NB_MODES } mode;

extern uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

void init_display();
void compute_display();
void display_strip();

#endif
