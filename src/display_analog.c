#include <stdint.h>

#include "config.h"
#include "clock.h"

#include "display_analog.h"

#define MINS_IN_HALF_A_DAY 720

// The current position of the hands
int h_pos = 0;
int m_pos = 0;
int s_pos = 0;

#ifndef COUNTERCLOCKWISE
// clockwise
inline uint16_t hour_to_pos(int h, int m)
{
  uint32_t mins = h * 60 + m;
  return POS_IN_A_TURN * ((mins + MINS_IN_HALF_A_DAY / 2) % MINS_IN_HALF_A_DAY) / MINS_IN_HALF_A_DAY; // clockwise
}

// Array of the discreet hands positions.
// It is precalculated and optimized so please dont freak out when seeing it as it is now
int m_to_p[60] = {
    ((POS_IN_A_TURN / 60) * 0 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 1 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 2 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 3 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 4 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 5 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 6 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 7 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 8 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 9 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 10 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 11 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 12 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 13 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 14 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 15 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 16 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 17 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 18 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 19 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 20 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 21 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 22 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 23 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 24 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 25 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 26 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 27 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 28 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 29 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 30 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 31 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 32 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 33 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 34 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 35 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 36 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 37 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 38 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 39 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 40 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 41 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 42 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 43 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 44 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 45 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 46 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 47 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 48 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 49 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 50 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 51 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 52 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 53 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 60) * 54 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 55 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 56 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 57 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 58 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 60) * 59 + POS_IN_A_TURN / 2) % POS_IN_A_TURN};
#else
// counterclockwise
inline uint16_t hour_to_pos(int h, int m)
{
  uint32_t mins = h * 60 + m;
  return POS_IN_A_TURN - (POS_IN_A_TURN * ((mins + MINS_IN_HALF_A_DAY / 2) % MINS_IN_HALF_A_DAY) / MINS_IN_HALF_A_DAY); // counterclockwise
}

// Array of the discreet hands positions.
// It is precalculated and optimized so please dont freak out when seeing it as it is now
int m_to_p[60] = {
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 0 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 1 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 2 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 3 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 4 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 5 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 6 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 7 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 8 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 9 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 10 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 11 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 12 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 13 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 14 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 15 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 16 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 17 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 18 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 19 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 20 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 21 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 22 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 23 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 24 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 25 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 26 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 27 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 28 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 29 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 30 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 31 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 32 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 33 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 34 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 35 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 36 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 37 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 38 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 39 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 40 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 41 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 42 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 43 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 44 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 45 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 46 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 47 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 48 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 49 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 50 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 51 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 52 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 53 + POS_IN_A_TURN / 2) % POS_IN_A_TURN),
    POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 54 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 55 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 56 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 57 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 58 + POS_IN_A_TURN / 2) % POS_IN_A_TURN), POS_IN_A_TURN - (((POS_IN_A_TURN / 60) * 59 + POS_IN_A_TURN / 2) % POS_IN_A_TURN)};
#endif

int hour_mark[12] = {
    ((POS_IN_A_TURN / 12) * 0 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 1 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 2 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 3 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 4 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 5 + POS_IN_A_TURN / 2) % POS_IN_A_TURN,
    ((POS_IN_A_TURN / 12) * 6 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 7 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 8 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 9 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 10 + POS_IN_A_TURN / 2) % POS_IN_A_TURN, ((POS_IN_A_TURN / 12) * 11 + POS_IN_A_TURN / 2) % POS_IN_A_TURN};

#define minute_to_pos(M, S) m_to_p[(M)]
#define seconds_to_pos(S) m_to_p[(S)]

void init_analog_display(uint16_t *display)
{
  h_pos = hour_to_pos(0, 0);
  m_pos = minute_to_pos(0, 0);
  s_pos = seconds_to_pos(0);

  for (int h = 0; h < 12; h++) {
    display[hour_mark[h]] |= HOUR_MARK;
  }

  display[h_pos] |= HOUR_HAND;
  display[m_pos] |= MINUTE_HAND;
  display[s_pos] |= SECOND_HAND;
}

void compute_analog_display(uint16_t *display)
{
  // Remove the hour and minute hands
  display[h_pos] &= ~(HOUR_HAND);
  display[m_pos] &= ~(MINUTE_HAND);
  // display[s_pos] &= ~(SECOND_HAND); // We do NOT reset the seconds every second
  if (seconds == 1) {
    // Reset the seconds
    for (int pos = 0; pos < POS_IN_A_TURN; pos++) {
      display[pos] &= ~(SECOND_HAND);
    }
  }

  h_pos = hour_to_pos(hours, minutes);
  m_pos = minute_to_pos(minutes, seconds);
  int new_s_pos = seconds_to_pos(seconds);

  display[h_pos] |= HOUR_HAND;
  display[m_pos] |= MINUTE_HAND;

#ifndef COUNTERCLOCKWISE
  int small_pos = s_pos;
  int big_pos = new_s_pos;
#else
  int small_pos = new_s_pos;
  int big_pos = s_pos;
#endif
  if (big_pos < small_pos) {
    for (int pos = 0; pos < big_pos; pos++) {
      display[pos] |= SECOND_HAND;
    }
    for (int pos = small_pos; pos < POS_IN_A_TURN; pos++) {
      display[pos] |= SECOND_HAND;
    }
  }
  for (int pos = small_pos; pos <= big_pos; pos++) {
    display[pos] |= SECOND_HAND;
  }
  s_pos = new_s_pos;
}
