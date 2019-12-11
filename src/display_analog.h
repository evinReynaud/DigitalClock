#ifndef __DISPLAY_ANALOG_H__
#define __DISPLAY_ANALOG_H__

#ifndef POS_IN_A_TURN
#undef POS_IN_A_TURN
#define POS_IN_A_TURN 10800
#endif

#define LEDS_OFF    0b0000000000000000
#define LEDS_ON     0b1111111111111111
#define NO_HAND     0b0000000000000000
#define HOUR_MARK   0b0110000000000000
#define SECOND_HAND 0b1000000000000000
#define MINUTE_HAND 0b0000111111110000
#define HOUR_HAND   0b0000000011111111

extern uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

void init_display();
void compute_display();
void display_strip();

#endif
