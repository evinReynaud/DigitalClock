#include <stdio.h>

#include "leds.h"
#include "test.h"

#include "display_analog.h"

// pos: 0 to 21600

// clockwise
int hour_to_pos(int h, int m)
{
  int mins = h*60 + m;
  char b[256];
  sprintf(b, "1: %d %d %d\n", h, m, mins);
  print(b);
  return ((mins+720)%1440)*15; // clockwise 720 = 24*60 / 2, 15 = 21600/1440
}

int m_to_p[60] = {10800, 11160, 11520, 11880, 12240, 12600, 12960, 13320, 13680, 14040, 14400, 14760, 15120, 15480, 15840, 16200, 16560, 16920, 17280, 17640, 18000, 18360, 18720, 19080, 19440, 19800, 20160, 20520, 20880, 21240, 0, 360, 720, 1080, 1440, 1800, 2160, 2520, 2880, 3240, 3600, 3960, 4320, 4680, 5040, 5400, 5760, 6120, 6480, 6840, 7200, 7560, 7920, 8280, 8640, 9000, 9360, 9720, 10080, 10440};

int minute_to_pos(int m, int s)
{
  return m_to_p[m];
}

int seconds_to_pos(int s)
{
  return m_to_p[s];
}

int get_hands(int pos)
{
  int leds = LEDS_OFF;
  if(pos == hour_to_pos(hours, minutes))
    leds |= HOUR_HAND;
  if(pos == minute_to_pos(minutes, seconds))
    leds |= MINUTE_HAND;
  if((seconds < 30  &&  pos >= 10800 && pos <= seconds_to_pos(seconds))
  || (seconds >= 30 && (pos >= 10800 || pos <= seconds_to_pos(seconds))))
    leds |= SECOND_HAND;
  // if(pos == seconds_to_pos_ccw(seconds))
  //   leds |= SECOND_HAND;

  char b[256];
  sprintf(b, "%02d:%02d:%02d\n%d %d %d\n%04x\n", hours, minutes, seconds, hour_to_pos(hours, minutes), minute_to_pos(minutes, seconds), seconds_to_pos(seconds), leds);
  print(b);
  return leds;
}

// counterclockwise
int hour_to_pos_ccw(int h, int m)
{
  int mins = h*60 + m;
  return 21600 - ((mins+720)%1440)*15; // counterclockwise
}

 int m_to_p_ccw[60] = {10800, 10440, 10080, 9720, 9360, 9000, 8640, 8280, 7920, 7560, 7200, 6840, 6480, 6120, 5760, 5400, 5040, 4680, 4320, 3960, 3600, 3240, 2880, 2520, 2160, 1800, 1440, 1080, 720, 360, 21600, 21240, 20880, 20520, 20160, 19800, 19440, 19080, 18720, 18360, 18000, 17640, 17280, 16920, 16560, 16200, 15840, 15480, 15120, 14760, 14400, 14040, 13680, 13320, 12960, 12600, 12240, 11880, 11520, 11160};

int minute_to_pos_ccw(int m, int s)
{
  return m_to_p_ccw[m];
}

int seconds_to_pos_ccw(int s)
{
  return m_to_p_ccw[s];
}

int get_hands_ccw(int pos)
{
  int leds = LEDS_OFF;
  if(pos == hour_to_pos_ccw(hours, minutes))
    leds |= HOUR_HAND;
  if(pos == minute_to_pos_ccw(minutes, seconds))
    leds |= MINUTE_HAND;
  if((seconds < 30  &&  pos <= 10800 && pos >= seconds_to_pos(seconds))
  || (seconds >= 30 && (pos <= 10800 || pos >= seconds_to_pos(seconds))))
    leds |= SECOND_HAND;

  // if(pos == seconds_to_pos_ccw(seconds))
  //   leds |= SECOND_HAND;
  return leds;
}

void display_strip()
{
  int leds = LEDS_OFF;
  int pos = get_arc_min();
  if(rotate == CLOCKWISE){
    leds_on(get_hands(pos));
  }
  else {
    leds_on(get_hands_ccw(pos));
  }
}
