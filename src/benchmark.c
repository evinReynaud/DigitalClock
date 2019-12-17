#include <stdio.h>

#include "display.h"
#include "position.h"
#include "pos_timer.h"
#include "benchmark.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "interface.h"
#include "leds.h"
volatile double timeInInterrup = 0;
volatile double analogTime = 0;
volatile double digitalTime = 0;
volatile double displayTime = 0;
volatile int count = 0;
volatile int receive = 0;


#define N 10
#define prescale 1024
#define foscms  13000
#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC / 16 / BAUD - 1

void initBenchmark()
{
  pos_timer_init();
  bluetooth_init();
  pos_timer_init();
  // receive_init();
  leds_init();
}

void getTimes()
{
  //bluetooth_transmit("start getTimes\n");
  for(;;)
  {
    analogTime += getAnalogTime();
    digitalTime += getDigitalTime();
    displayTime += getDisplayTime();
    //bluetooth_transmit("in process\n");
    count++;

  }
  analogTime  /= count;
  digitalTime /= count;
  displayTime /= count;
  //bluetooth_transmit("end getTimes\n");

}

double getAnalogTime()
{
  //bluetooth_transmit("start analogTime\n");

  uint16_t debut, fin;
  mode = ANALOG;
  pos_timer_start();
  debut = pos_timer_read();
  compute_display();
  fin=pos_timer_read();
  char b[1000];
  int duree = (fin-debut);
  sprintf(b,"analog time %d\n",duree);
  bluetooth_transmit(b);
  return duree;
}



double getDigitalTime()
{
  //bluetooth_transmit("start digitalTime\n");

  uint16_t debut, fin;
  pos_timer_start();
  debut = pos_timer_read();
  mode = DIGITAL;
  compute_display();
  pos_timer_stop();
  fin = pos_timer_read();
  int duree = (fin-debut);

  //bluetooth_transmit("end digitalTime\n");
  //double duree = difftime(fin, debut);
  char b[1000];
  sprintf(b,"digital time %d\n",duree);
  bluetooth_transmit(b);

  return duree;

}



double getDisplayTime()
{
  //bluetooth_transmit("start displayTime\n");
  pos_timer_write(1);
  uint16_t debut, fin;
  pos_timer_start();
  effethall_init();
  debut = pos_timer_read();
  display_strip();
  pos_timer_stop();
  fin = pos_timer_read();
  int duree = (fin-debut);

  //bluetooth_transmit("end displayTime\n");
  char b[1000];
  sprintf(b,"display time %d\n",duree);
  bluetooth_transmit(b);
  return duree;
}
