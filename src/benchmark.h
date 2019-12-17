#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__



extern volatile  int timeInInterrup;
extern volatile  int analogTime ;
extern volatile  int digitalTime ;
extern volatile  int displayTime ;

void initBenchmark();

int getAnalogTime();
//void receive_init();


int getDigitalTime();

int getDisplayTime();
void getTimes();


//extern volatile int count;
//extern volatile int receive ;


#endif
