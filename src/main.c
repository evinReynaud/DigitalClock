#include <stdio.h>
#include <string.h>
#include <avr/io.h>

#include "leds.h"
#include "bluetooth.h"
#include "display.h"
#include "clock.h"
#include "interface.h"
#include "position.h"
#include "timer.h"

#ifdef BENCHMARK
#include "benchmark.h"
#endif

void system_init()
{
  mode = ANALOG;
  set_time(0, 0, 0);
  bluetooth_init();
  #ifdef VERBOSE
  debug_printf("=================\nStart init\n");
  debug_printf("Init leds\n");
  #endif
  leds_init();
  leds_on(LEDS_ON);
  #ifdef VERBOSE
  debug_printf("Init timer\n");
  #endif
  timer_init();
  #ifdef VERBOSE
  debug_printf("Init position\n");
  #endif
  position_init();
  #ifdef VERBOSE
  debug_printf("Init display\n");
  #endif
  init_display();
  #ifdef VERBOSE
  debug_printf("Start timer\n");
  #endif
  timer_start();

  leds_on(LEDS_OFF);

  #ifdef VERBOSE
  debug_printf("Init done\n\n");
  #endif
}

void hard_reset()
{
  // turn on AVR watchdog and force it to restart the chip by infinite loop
  WDTCR=0x18;
  WDTCR=0x08;
  while(1);
}

int clock_main()
{
  system_init();
  send_info();
  while (1) {
    if(reset) {
      hard_reset();
    }

    interface();
    update_time();
    display_strip();

    // Reset hall effect interruption
    check_position();
  }
  return 0;
}

#ifdef BENCHMARK
int getStop()
{
  if(bluetooth_data_ready()) {
    char data[16];
    bluetooth_wait_for_data(data);
    if(strcmp(data,"stop")==0)
      return 1;
    else
      return 0;
  }
  else return 0;
}

int benchmark_main()
{
  initBenchmark();

  bluetooth_transmit("Type start to begin benchmark\n");
  int count = 0;
  char data[256];
  bluetooth_wait_for_data(data);
  int stop = 0;
  if(strcmp(data,"start")==0) {
    do {
        getTimes();
        count++;
        stop = getStop();
    } while(!stop && count<100);
  }

  char b[256];
  sprintf(b,"Time In Interruption %d\n Time for analog display %d\n Time for digital display %d\n Time for displaying a strip %d\n Number of repetition  %d\n", timeInInterrup,analogTime,digitalTime,displayTime,count);
  bluetooth_transmit(b);
  bluetooth_transmit("end\n");

  return 0;
}
#endif

int main()
{
  #ifdef BENCHMARK
  return benchmark_main();
  #else
  return clock_main();
  #endif
}
