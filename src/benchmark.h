#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__
#include <stdlib.h>


void initBenchmark();

double getAnalogTime();
void receive_init();


double getDigitalTime();

double getDisplayTime();
void getTimes();

extern volatile double timeInInterrup;
extern volatile double analogTime;
extern volatile double digitalTime;
extern volatile double displayTime;
extern volatile int count;
extern volatile int receive ;


#endif
