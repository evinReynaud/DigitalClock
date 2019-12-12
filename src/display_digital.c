#include <stdio.h>
#include <string.h>

#include "clock.h"
#include "position.h"
#include "letters.h"

#include "debug.h"

#include "display_digital.h"

#define MAX(X, Y) ((X) > (Y)) ? (X) : (Y)
#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

uint16_t** chars = NULL;

#define LINE_WIDTH 5*POS_IN_A_TURN/360


#ifndef COUNTERCLOCKWISE
// clockwise
#define FIRST_LINE_START_POS POS_IN_A_TURN/4
#define FIRST_LINE_STOP_POS 3*POS_IN_A_TURN/4
#define SECOND_LINE_START_POS POS_IN_A_TURN/4
#define SECOND_LINE_STOP_POS 3*POS_IN_A_TURN/4

#else
// counterclockwise
#define WRITING_START_POS 3*POS_IN_A_TURN/4

#endif


void init_digital_display(uint16_t * display)
{
  chars = get_char_table();
  (void) display;
}

// void compute_display_slow() {
//   h_pos = hour_to_pos(hours, minutes);
//   m_pos = minute_to_pos(minutes, seconds);
//   s_pos = seconds_to_pos(seconds);
//   for(int pos = 0; pos < POS_IN_A_TURN; pos++){
//     uint16_t leds = get_hands(pos, h_pos, m_pos, s_pos);
//     if(display[pos] != leds)
//       display[pos] = leds;
//   }
// }

unsigned int pixel_length(char * line)
{
  int len = 0;
  for(int c = 0; line[c] != '\0'; c++){
    len += (chars[(int)line[c]][0]+1)*LINE_WIDTH;
  }
  return len - LINE_WIDTH;
}

void write_in(uint16_t * display, int pos, uint16_t val)
{
  // char b[8];
  // sprintf(b, "%d ", pos);
  // debug_printf(b);
  while(pos < 0){
    pos = POS_IN_A_TURN+pos;
  }
  // sprintf(b, "%d ", pos);
  // debug_printf(b);
  while(pos >= POS_IN_A_TURN){
    pos = pos-POS_IN_A_TURN;
  }
  // sprintf(b, "%d\n", pos);
  // debug_printf(b);
  display[pos] = val;
}

#define CHAR_BIT 8

uint16_t binary_mirror(uint16_t num)
{
  uint16_t r = num; // r will be reversed bits of num; first get LSB of num
  int s = sizeof(num) * CHAR_BIT - 1; // extra shift needed at end

  for (num >>= 1; num; num >>= 1)
  {
    r <<= 1;
    r |= num & 1;
    s--;
  }
  r <<= s; // shift when num's highest bits are zero
  return r;
}

int write_first_line(uint16_t * display, char * line)
{
  int len = pixel_length(line);
  int display_pos = MAX(FIRST_LINE_START_POS+(FIRST_LINE_STOP_POS - FIRST_LINE_START_POS - len)/2, FIRST_LINE_START_POS);

  for(unsigned int c = 0; line[c] != '\0'; c++){
    for(unsigned int i = 1; i <= chars[(int)line[c]][0]; i++){
      for(unsigned int j = 0; j < LINE_WIDTH; j++){
        if(display_pos <= FIRST_LINE_STOP_POS){
          write_in(display, display_pos, chars[(int)line[c]][i]);
          display_pos++;
          // display[display_pos++] = chars[(int)line1[c]][i];
        }
        else {
          return 1;
        }
      }
    }
    for(unsigned int j = 0; j < LINE_WIDTH; j++){
      if(display_pos <= FIRST_LINE_STOP_POS){
        write_in(display, display_pos, 0);
        display_pos++;
        // display[display_pos++] = 0;
      }
      else {
        return 1;
      }
    }
  }
  return 0;
}



int write_second_line(uint16_t * display, char * line)
{
  int len = pixel_length(line);
  int display_pos = MIN(len/2, SECOND_LINE_START_POS);

  for(unsigned int c = 0; line[c] != '\0'; c++){
    for(unsigned int i = 1; i <= chars[(int)line[c]][0]; i++){
      for(unsigned int j = 0; j < LINE_WIDTH; j++){
        if(display_pos >= SECOND_LINE_STOP_POS - POS_IN_A_TURN){
          write_in(display, display_pos, binary_mirror(chars[(int)line[c]][i]));
          display_pos--;
        }
        else {
          return 1;
        }
      }
    }
    for(unsigned int j = 0; j < LINE_WIDTH; j++){
      if(display_pos >= SECOND_LINE_STOP_POS - POS_IN_A_TURN){
        write_in(display, display_pos, 0);
        display_pos--;
      }
      else {
        return 1;
      }
    }
  }
  return 0;
}

// Returns 0 if no writting error occured, returns non-zero otherwise
int write_in_display(uint16_t * display, char * line1, char * line2)
{
  return write_first_line(display, line1) + write_second_line(display, line2);
}

void compute_digital_display(uint16_t * display)
{
  char line1[16] = {'\0'};
  char line2[16] = {'\0'};
  if(seconds%2){
    sprintf(line1, "%02d;%02d", hours, minutes);
    // sprintf(line2, "Lae !");
  }
  else {
    sprintf(line1, "%02d %02d", hours, minutes);
    // sprintf(line2, "Evin !");
  }
  // debug_printf(line1);
  // strcpy(line1, "Test !");
  sprintf(line2, "%02d", seconds);
  write_in_display(display, line1, line2);
}
