#include "leds.h"
#include "bluetooth.h"
#include "display.h"
#include "clock.h"
#include "interface.h"
#include "position.h"
#include "timer.h"
#include "effethall.h"
#include "debug.h"
#include <string.h>
#ifdef BENCHMARK
#include "benchmark.h"
#endif


void system_init(){
  mode = DIGITAL;
  hours = 0;
  minutes = 0;
  seconds = 0;
  bluetooth_init();
  debug_printf("=================\nStart init\n");
  debug_printf("Init leds\n");
  leds_init();
  leds_on(0xffff);
  debug_printf("Init timer\n");
  timer_init();
  debug_printf("Init position\n");
  position_init();
  debug_printf("Init display\n");
  init_display();
  debug_printf("Start timer\n");
  timer_start();

  leds_on(LEDS_OFF);

  debug_printf("Init done\n\n");
}

void soft_reset(){
  mode = DIGITAL;
  hours = 0;
  minutes = 0;
  seconds = 0;
  init_display();
  position_init();
}

int main()
{

  #ifdef BENCHMARK
  initBenchmark();
  bluetooth_transmit("Type start to begin benchmark\n");

  //if (strlen(data) == 0)
    //return;
  //bluetooth_transmit("Type start to begin benchmark \n");
  if(receive)
  {
    char data[256];
    bluetooth_wait_for_data(data);
    if(strcmp(data,"start"))
    {
      do
      {
         getTimes();
         if(receive)
         {
           char data[256];
           bluetooth_wait_for_data(data);
           receive = 0;
         }
      } while(strcmp(data,"stop"));
    }
    else
    {
      do {
        char data[256];
        bluetooth_wait_for_data(data);
        receive = 0;
      }while(strcmp(data,"start")==0 || strcmp(data,"stop")==1);
    }
  }

  char b[1000];
  sprintf(b,"Time In Interruption %lf\n Time for analog display %lf\n Time for digital display %lf\n Time for displaying a strip %lf\n Number of repetition  %d\n", timeInInterrup,analogTime,digitalTime,displayTime,count);
  bluetooth_transmit(b);
  bluetooth_transmit("end\n");

  #else
  system_init();
  send_info();
  while (1)
  {
    if (reset == 1){
      reset = 0;
      soft_reset();
    }
    if (reset == 2){
      reset = 0;
      system_init();
    }
    interface();
    update_time();
    display_strip();

    check_position();
  }
  #endif

  return 0;
}

// TODO:
// Weld new motor (Junior)
// Benchmark compute_display() for each mode, display_strip(), the hall effect interruption
//
