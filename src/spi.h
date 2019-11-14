#ifndef __SPI_H__
#define __SPI_H__

void SPI_master_init();

void SPI_master_transmit(char cData);

void SPI_master_EOC();

#endif
