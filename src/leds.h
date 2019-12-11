#ifndef __LEDS_H__
#define __LEDS_H__

#define LEDS_OFF    0b0000000000000000
#define LEDS_ON     0b1111111111111111

void leds_init();

/**
 * function leds_on turn on or off the leds according to the binary
 * representation of its input data (1 means on).
 * led 19 is the LSB and led 4 is the MSB
 */
void leds_on(unsigned int data);

#endif
