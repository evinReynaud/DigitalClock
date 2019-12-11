#include <stdio.h>

#include "leds.h"
#include "clock.h"
#include "position.h"

#include "debug.h"

#include "display_analog.h"

#define MINS_IN_HALF_A_DAY 720
// pos: 0 to 10800

#ifndef COUNTERCLOCKWISE
// clockwise
inline int hour_to_pos(int h, int m)
{
  int mins = h*60 + m;
  return (((mins+MINS_IN_HALF_A_DAY/2)%MINS_IN_HALF_A_DAY)*POS_IN_A_TURN)/MINS_IN_HALF_A_DAY; // clockwise
}

// Array of the discreet hands positions.
// It is precompiled and optimized so please dont freak out when seeing it as it is now
int m_to_p[60] = {
  ((POS_IN_A_TURN/60)*0+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*1+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*2+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*3+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*4+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*5+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*6+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*7+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*8+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*9+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*10+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*11+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*12+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*13+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*14+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*15+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*16+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*17+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*18+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*19+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*20+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*21+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*22+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*23+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*24+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*25+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*26+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*27+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*28+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*29+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*30+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*31+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*32+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*33+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*34+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*35+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*36+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*37+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*38+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*39+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*40+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*41+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*42+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*43+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*44+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*45+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*46+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*47+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*48+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*49+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*50+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*51+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*52+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*53+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/60)*54+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*55+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*56+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*57+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*58+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/60)*59+POS_IN_A_TURN/2)%POS_IN_A_TURN
};
#else
// counterclockwise
inline int hour_to_pos(int h, int m)
{
  int mins = h*60 + m;
  // char b[256];
  // sprintf(b, "1: %d %d %d\n", h, m, mins);
  // print(b);
  return POS_IN_A_TURN - (((mins+MINS_IN_HALF_A_DAY/2)%MINS_IN_HALF_A_DAY)*POS_IN_A_TURN)/MINS_IN_HALF_A_DAY); // clockwise
}

// Array of the discreet hands positions.
// It is precompiled and optimized so please dont freak out when seeing it as it is now
int m_to_p[60] = {
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*0+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*1+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*2+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*3+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*4+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*5+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*6+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*7+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*8+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*9+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*10+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*11+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*12+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*13+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*14+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*15+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*16+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*17+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*18+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*19+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*20+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*21+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*22+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*23+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*24+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*25+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*26+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*27+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*28+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*29+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*30+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*31+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*32+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*33+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*34+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*35+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*36+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*37+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*38+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*39+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*40+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*41+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*42+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*43+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*44+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*45+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*46+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*47+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*48+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*49+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*50+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*51+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*52+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*53+POS_IN_A_TURN/2)%POS_IN_A_TURN),
  POS_IN_A_TURN - (((POS_IN_A_TURN/60)*54+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*55+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*56+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*57+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*58+POS_IN_A_TURN/2)%POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN/60)*59+POS_IN_A_TURN/2)%POS_IN_A_TURN)
};
#endif

int hour_mark[12] = {
  ((POS_IN_A_TURN/12)*0+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*1+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*2+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*3+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*4+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*5+POS_IN_A_TURN/2)%POS_IN_A_TURN,
  ((POS_IN_A_TURN/12)*6+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*7+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*8+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*9+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*10+POS_IN_A_TURN/2)%POS_IN_A_TURN, ((POS_IN_A_TURN/12)*11+POS_IN_A_TURN/2)%POS_IN_A_TURN
};

#define minute_to_pos(M, S) m_to_p[(M)]
#define seconds_to_pos(S) m_to_p[(S)]
// int minute_to_pos(int m, int s)
// {
//   return m_to_p[m];
// }
//
// int seconds_to_pos(int s)
// {
//   return m_to_p[s];
// }

uint16_t get_hands(int pos, int h_pos, int m_pos, int s_pos)
{
  uint16_t leds = LEDS_OFF;
  if(pos == h_pos)
    leds |= HOUR_HAND;
  if(pos == m_pos)
    leds |= MINUTE_HAND;
  #ifndef COUNTERCLOCKWISE
  if((seconds < 30  &&  pos >= POS_IN_A_TURN/2 && pos <= s_pos)
  || (seconds >= 30 && (pos >= POS_IN_A_TURN/2 || pos <= s_pos)))
  #else
  if((seconds < 30  &&  pos <= POS_IN_A_TURN/2 && pos >= s_pos)
  || (seconds >= 30 && (pos <= POS_IN_A_TURN/2 || pos >= s_pos)))
  #endif
    leds |= SECOND_HAND;

  // char b[256];
  // sprintf(b, "%02d:%02d:%02d\n%d %d %d\n%04x\n", hours, minutes, seconds, hour_to_pos(hours, minutes), minute_to_pos(minutes, seconds), seconds_to_pos(seconds), leds);
  // print(b);
  return leds;
}

uint16_t display[POS_IN_A_TURN]; // The array in which we store our led configs

// The current position of the hands
int h_pos = 0;
int m_pos = 0;
int s_pos = 0;

void debug_show_array(){
  char b[16];
  for(int pos = 0; pos < POS_IN_A_TURN; pos++){
    if(display[pos] != 0){
      sprintf(b, "%03d: %x\n", pos, display[pos]);
      debug_printf(b);
    }
  }
}

inline void init_display_array(){
  for(int pos = 0; pos < POS_IN_A_TURN; pos++){
    display[pos] = NO_HAND;
  }
}

void init_display(){
  h_pos = hour_to_pos(0, 0);
  m_pos = minute_to_pos(0, 0);
  s_pos = seconds_to_pos(0);

  init_display_array();

  for(int h = 0; h < 12; h++) {
    display[hour_mark[h]] |= HOUR_MARK;
  }

  display[h_pos] |= HOUR_HAND;
  display[m_pos] |= MINUTE_HAND;
  display[s_pos] |= SECOND_HAND;

  // init_display_array();
  // display[0] = 0b1111000000000000;
  // display[POS_IN_A_TURN/4] = 0b0000111100000000;
  // display[POS_IN_A_TURN/2] = 0b0000000011110000;
  // display[3*POS_IN_A_TURN/4] = 0b0000000000001111;

  debug_show_array();
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

void compute_display() {

  // Remove the hour and minute hands
  display[h_pos] &= ~(HOUR_HAND);
  display[m_pos] &= ~(MINUTE_HAND);
  // display[s_pos] &= ~(SECOND_HAND); // We do NOT reset the seconds every second
  if(seconds == 1){ // Reset the seconds
    for(int pos = 0; pos < POS_IN_A_TURN; pos++){
      display[pos] &= ~(SECOND_HAND);
    }
  }

  h_pos = hour_to_pos(hours, minutes);
  m_pos = minute_to_pos(minutes, seconds);
  int new_s_pos = seconds_to_pos(seconds);

  char b[64];
  sprintf(b, "%d:%d:%u\n%d, %d, %d\n\n", hours, minutes, seconds, h_pos, m_pos, new_s_pos);
  debug_printf(b);

  display[h_pos] |= HOUR_HAND;
  display[m_pos] |= MINUTE_HAND;
  if(new_s_pos < s_pos){
    for(int pos = 0; pos < new_s_pos; pos++){
      display[pos] |= SECOND_HAND;
    }
    for(int pos = s_pos; pos < POS_IN_A_TURN; pos++){
      display[pos] |= SECOND_HAND;
    }
  }
  for(int pos = s_pos; pos <= new_s_pos; pos++){
    display[pos] |= SECOND_HAND;
  }
  s_pos = new_s_pos;
}

void display_strip()
{
  leds_on(display[get_pos()]);

  // uint32_t pos = get_pos();
  // leds_on(display[pos]);
  // leds_on(LEDS_OFF);
  // char b[20];
  // sprintf(b, "%d\n", pos);
  // debug_printf(b);
}
