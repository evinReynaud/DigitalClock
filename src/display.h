#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifndef POS_IN_A_TURN
#undef POS_IN_A_TURN
#define POS_IN_A_TURN 360
#endif

extern uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

void init_display();
void compute_display();
void display_strip();

#endif
