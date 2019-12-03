#ifndef __DISPLAY_ANALOG_H__
#define __DISPLAY_ANALOG_H__

#ifndef POS_IN_A_TURN
#undef POS_IN_A_TURN
#define POS_IN_A_TURN 10800
#endif

#define LEDS_OFF    0b0000000000000000
#define NO_HAND     0b0000000000000000
#define HOUR_HAND   0b0000001111111111
#define MINUTE_HAND 0b0011111111110000
#define SECOND_HAND 0b1000000000000000

void compute_display();
void display_strip();

#endif
