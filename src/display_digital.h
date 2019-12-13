#ifndef __DISPLAY_DIGITAL_H__
#define __DISPLAY_DIGITAL_H__

void init_digital_display(uint16_t *display);
void compute_digital_display(uint16_t *display);
void compute_custom_display(uint16_t *display);
void compute_love_display(uint16_t *display);

extern char line1[16];
extern char line2[16];

#endif
