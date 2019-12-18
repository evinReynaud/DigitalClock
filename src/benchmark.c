#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "position.h"
#include "pos_timer.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "interface.h"
#include "leds.h"

#include "benchmark.h"

#define N 10
#define prescale 1024
#define foscms  13000

volatile  int timeInInterrup =0;
volatile  int analogTime =0 ;
volatile  int digitalTime =0;
volatile  int displayTime =0;

void initBenchmark()
{
  pos_timer_init();
  bluetooth_init();
  leds_init();
  effethall_init();
}

void getTimes()
{
  analogTime += getAnalogTime();
  digitalTime += getDigitalTime();
  displayTime += getDisplayTime();
}

int getAnalogTime()
{
  uint16_t begining, end;

  mode = ANALOG;
  pos_timer_write(1);
  pos_timer_start();
  begining = pos_timer_read();

  compute_display();

  end=pos_timer_read();
  pos_timer_stop();
  pos_timer_write(1);

  return end-begining;
}

int getDigitalTime()
{
  uint16_t begining, end;

  mode = DIGITAL;
  pos_timer_write(1);
  pos_timer_start();
  begining = pos_timer_read();

  compute_display();

  end = pos_timer_read();
  pos_timer_stop();
  pos_timer_write(1);

  return end-begining;
}

int getDisplayTime()
{
  uint16_t begining, end;

  effethall_init();
  pos_timer_write(1);
  pos_timer_start();
  begining = pos_timer_read();

  display_strip();

  end = pos_timer_read();
  pos_timer_write(1);
  pos_timer_stop();

  return end-begining;
}
