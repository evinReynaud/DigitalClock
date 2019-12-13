#ifndef __DISPLAY_DIGITAL_H__
#define __DISPLAY_DIGITAL_H__

extern char line1[16];
extern char line2[16];

void init_digital_display(uint16_t * display);

void compute_digital_display(uint16_t * display);

#endif
