#include "display.h"
#include "position.h"
#include "pos_timer.h"
#include "benchmark.h"
#include "bluetooth.h"
#include "clock.h"
#include "effethall.h"
#include "interface.h"
#include "leds.h"

#include <stdlib.h>

// extern volatile int timeInInterrup;
// extern volatile int analogTime ;
// extern volatile int digitalTime;
// extern volatile int displayTime;

// volatile double timeInInterrup=0;
// volatile double analogTime =0;
// volatile double digitalTime = 0;
// volatile double displayTime = 0;
//volatile int count = 0;
//volatile int receive = 0;


volatile  int timeInInterrup =0;
volatile  int analogTime =0 ;
volatile  int digitalTime =0;
volatile  int displayTime =0;



#define N 10
#define prescale 1024
#define foscms  13000


void initBenchmark()
{
  pos_timer_init();
  bluetooth_init();
  leds_init();
  effethall_init();
}

// ISR(USART0_RX_vect)
// {
//   receive = 1;
// }
//
// void receive_init()
// {
//   sei();
//   UCSR0B = _BV(RXCIE0);
// }

void getTimes()
{
  //bluetooth_transmit("start getTimes\n");

    analogTime += getAnalogTime();
    digitalTime += getDigitalTime();
    displayTime += getDisplayTime();

    //char b[1000];
    //sprintf(b,"Time In Interruption %d\n Time for analog display %d\n Time for digital display %d\n Time for displaying a strip %d\n",timeInInterrup,analogTime,digitalTime,displayTime);
    //bluetooth_transmit(b);
    //bluetooth_transmit("in process\n");
    // count++;
    // analogTime  /= count;
    // digitalTime /= count;
    // displayTime /= count;
  //bluetooth_transmit("end getTimes\n");

}

int getAnalogTime()
{
  //bluetooth_transmit("start analogTime\n");

  uint16_t debut, fin;
  mode = ANALOG;
  pos_timer_start();
  debut = pos_timer_read();
  compute_display();
  fin=pos_timer_read();
  pos_timer_write(1);
  pos_timer_stop();
  // char b[1000];
  int duree = (fin-debut);
  // sprintf(b,"analog time %d\n",duree);
  // bluetooth_transmit(b);
  return duree;
}



int getDigitalTime()
{
  //bluetooth_transmit("start digitalTime\n");

  uint16_t debut, fin;
  pos_timer_start();
  debut = pos_timer_read();
  mode = DIGITAL;
  compute_display();
  fin = pos_timer_read();
  pos_timer_write(1);
  pos_timer_stop();
  int duree = (fin-debut);

  //bluetooth_transmit("end digitalTime\n");
  // //double duree = difftime(fin, debut);
  // char b[1000];
  // sprintf(b,"digital time %d\n",duree);
  // bluetooth_transmit(b);

  return duree;

}



int getDisplayTime()
{
  //bluetooth_transmit("start displayTime\n");
  pos_timer_write(1);
  uint16_t debut, fin;
  pos_timer_start();
  effethall_init();
  debut = pos_timer_read();
  display_strip();
  fin = pos_timer_read();
  pos_timer_write(1);
  pos_timer_stop();
  int duree = (fin-debut);
  //bluetooth_transmit("end displayTime\n");
  // char b[1000];
  // sprintf(b,"display time %d\n",duree);
  // bluetooth_transmit(b);
  return duree;
}
