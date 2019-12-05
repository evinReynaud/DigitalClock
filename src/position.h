#ifndef __POSITION_H__
#define __POSITION_H__

#include "bluetooth.h"
#include "effethall.h"
#include "spi.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "config.h"

extern volatile uint16_t countPerTour;
extern volatile int etat ;
extern volatile int follow ;


void timer_init_postion(void);
void timer_start_position(void);
void TIM16_ReadTCNT3( void );
void timer_stop_position(void);
int getPos(void);
void TIM16_WriteTCNT3( unsigned int i );
void SPI_master_transmit(uint16_t data);
#endif
