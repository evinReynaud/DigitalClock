#ifndef __DISPLAY_DIGITAL_H__
#define __DISPLAY_DIGITAL_H__

#ifndef POS_IN_A_TURN
#undef POS_IN_A_TURN
#define POS_IN_A_TURN 360
#endif

void init_digital_display(uint16_t * display);
void compute_digital_display(uint16_t * display);

#endif
