#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "config.h"
#include "clock.h"
#include "position.h"
#include "letters.h"

#include "display_digital.h"

#define MAX(X, Y) ((X) > (Y)) ? (X) : (Y)
#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

char line1[16] = {'\0'};
char line2[16] = {'\0'};

uint16_t **chars = NULL;

#ifndef MAX_LINE_WIDTH
#define MAX_LINE_WIDTH 5 * POS_IN_A_TURN / 360
#endif

#ifndef MIN_LINE_WIDTH
#define MIN_LINE_WIDTH 2 * POS_IN_A_TURN / 360
#endif

#ifndef COUNTERCLOCKWISE
// clockwise
#define FIRST_LINE_START_POS POS_IN_A_TURN / 4
#define FIRST_LINE_STOP_POS 3 * POS_IN_A_TURN / 4
#define SECOND_LINE_START_POS POS_IN_A_TURN / 4
#define SECOND_LINE_STOP_POS 3 * POS_IN_A_TURN / 4

#else
// counterclockwise

#endif

void reset_display(uint16_t *display)
{
  for (int pos = 0; pos < POS_IN_A_TURN; pos++) {
    display[pos] = 0;
  }
}

void init_digital_display(uint16_t *display)
{
  if(chars == NULL)
    chars = get_char_table(chars);
  line1[0] = '\0';
  line2[0] = '\0';

  reset_display(display);
}

unsigned int pixel_length_for_width(char *line, unsigned int line_width)
{
  int len = 0;
  for (int c = 0; line[c] != '\0'; c++) {
    len += (chars[(int)line[c]][0] + 1) * line_width;
  }
  return len - line_width;
}

unsigned int pixel_length(char *line, unsigned int *line_width, unsigned int max_len)
{
  if (line_width == NULL || max_len == 0) {
    return pixel_length_for_width(line, MAX_LINE_WIDTH);
  }
  unsigned int width = MAX_LINE_WIDTH;
  unsigned int len = pixel_length_for_width(line, width);
  while (len > max_len && width >= MIN_LINE_WIDTH) {
    if (len > max_len)
      width--;
    len = pixel_length_for_width(line, width);
  }

  *line_width = width;
  return len;
}

void write_in(uint16_t *display, int pos, uint16_t val)
{
  while (pos < 0)
    pos += POS_IN_A_TURN;
  pos %= POS_IN_A_TURN;
  display[pos] = val;
}

#define CHAR_BIT 8

uint16_t binary_mirror(uint16_t num)
{
  uint16_t r = num;                   // r will be reversed bits of num; first get LSB of num
  int s = sizeof(num) * CHAR_BIT - 1; // extra shift needed at end

  for (num >>= 1; num; num >>= 1) {
    r <<= 1;
    r |= num & 1;
    s--;
  }
  r <<= s; // shift when num's highest bits are zero

  // Shift to the bottom
  s = 3;
  while (s) {
    r <<= 1;
    s--;
  }
  return r;
}

int write_first_line(uint16_t *display, char *line)
{
  unsigned int line_width;
  int len = pixel_length(line, &line_width, FIRST_LINE_STOP_POS - FIRST_LINE_START_POS);
  int display_pos = MAX(FIRST_LINE_START_POS + (FIRST_LINE_STOP_POS - FIRST_LINE_START_POS - len) / 2, FIRST_LINE_START_POS);

  for (unsigned int c = 0; line[c] != '\0'; c++) {
    for (unsigned int i = 1; i <= chars[(int)line[c]][0]; i++) {
      for (unsigned int j = 0; j < line_width; j++) {
        if (display_pos < FIRST_LINE_STOP_POS) {
          write_in(display, display_pos++, chars[(int)line[c]][i]);
        }
        else {
          return 1;
        }
      }
    }
    for (unsigned int j = 0; j < line_width; j++) {
      if (display_pos < FIRST_LINE_STOP_POS) {
        write_in(display, display_pos++, 0);
      }
      else {
        return 1;
      }
    }
  }
  return 0;
}

int write_second_line(uint16_t *display, char *line)
{
  unsigned int line_width;
  int len = pixel_length(line, &line_width, SECOND_LINE_START_POS + POS_IN_A_TURN - SECOND_LINE_STOP_POS);
  int display_pos = MIN(len / 2, SECOND_LINE_START_POS);

  for (unsigned int c = 0; line[c] != '\0'; c++) {
    for (unsigned int i = 1; i <= chars[(int)line[c]][0]; i++) {
      for (unsigned int j = 0; j < line_width; j++) {
        if (display_pos > SECOND_LINE_STOP_POS - POS_IN_A_TURN) {
          write_in(display, display_pos--, binary_mirror(chars[(int)line[c]][i]));
        }
        else {
          return 1;
        }
      }
    }
    for (unsigned int j = 0; j < line_width; j++) {
      if (display_pos > SECOND_LINE_STOP_POS - POS_IN_A_TURN) {
        write_in(display, display_pos--, 0);
      }
      else {
        return 1;
      }
    }
  }
  return 0;
}

// Returns 0 if no writting error occured, returns non-zero otherwise
int write_in_display(uint16_t *display, char *line1, char *line2)
{
  return write_first_line(display, line1) + write_second_line(display, line2);
}

void get_data_to_print(char *line1, char *line2)
{
  if (seconds % 2) {
    sprintf(line1, "%02d:%02d", hours, minutes);
  }
  else {
    sprintf(line1, "%02d %02d", hours, minutes);
  }
  sprintf(line2, "%02d", seconds);
}

void get_data_to_print_love(char *line1, char *line2)
{
  switch(seconds%4) {
    case 0:
    sprintf(line1, "%c", 2);
    break;

    case 1:
    sprintf(line2, "LOVE");
    break;

    case 2:
    sprintf(line1, "%c", 3);
    break;

    case 3:
    sprintf(line2, "YOU");
    break;
  }
}

void compute_digital_display(uint16_t *display)
{
  get_data_to_print(line1, line2);
  reset_display(display);
  write_in_display(display, line1, line2);
}

void compute_custom_display(uint16_t *display)
{
  reset_display(display);
  write_in_display(display, line1, line2);
}

void compute_love_display(uint16_t *display)
{
  get_data_to_print_love(line1, line2);
  reset_display(display);
  write_in_display(display, line1, line2);
}
