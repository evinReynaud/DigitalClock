#ifndef __DISPLAY_ANALOG_H__
#define __DISPLAY_ANALOG_H__

#include <stdint.h>

#define NO_HAND     0b0000000000000000
#define HOUR_MARK   0b0110000000000000
#define SECOND_HAND 0b1000000000000000
#define MINUTE_HAND 0b0000111111111111
#define HOUR_HAND   0b0000000011111111

void init_analog_display(uint16_t * display);

void compute_analog_display(uint16_t * display);

#endif
