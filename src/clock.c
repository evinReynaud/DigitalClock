#include "timer.h"
#include "display.h"

#include "clock.h"

int8_t hours = 0;
int8_t minutes = 0;

char hour_changed = 1;
char minute_changed = 1;
uint8_t prev_second = 0;

void update(int8_t * to_update, int8_t based_on, char * already_updated, int max_value)
{
  if(based_on == 0 && !(*already_updated)) {
    *to_update = (*to_update + 1) % max_value;
    *already_updated = 1;
  }
  else if (based_on == 1) {
    *already_updated = 0;
  }
}

inline void update_hour()
{
  update(&hours, minutes, &hour_changed, 24);
}

inline void update_minute()
{
  update(&minutes, seconds, &minute_changed, 60);
}

void update_time()
{
  update_minute();
  update_hour();

  if (prev_second != seconds)
  {
    prev_second = seconds;
    compute_display();
  }
}


#define MAX(X, Y) ((X) > (Y)) ? (X) : (Y)

void set_time(int8_t h, int8_t m, int8_t s)
{
  hours = MAX(h%24, 0);
  minutes = MAX(m%60, 0);
  seconds = MAX(s%60, 0);

  hour_changed = minutes ? 0 : 1;
  minute_changed = seconds ? 0 : 1;
  prev_second = 61;
}
