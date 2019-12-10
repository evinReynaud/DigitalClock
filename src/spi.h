#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

void SPI_master_init();

void SPI_master_transmit_char(char cData);

void SPI_master_transmit(uint16_t data);

void SPI_master_EOC();

#endif
