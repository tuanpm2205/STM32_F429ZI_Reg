#ifndef __SPI_H
#define __SPI_H

#include "TYPE.h"

typedef struct{
	__REG CR1;
	__REG CR2;
	__REG SR;
	__REG DR;
	__REG CRCPR;
	__REG RXCRCR;
	__REG TXCRCR;
	__REG I2SCFGR;
	__REG I2SPR;
}SPI_Typedef;

#define SPI1_ADDRESS_BASE 				0x40013000UL
#define SPI1											((volatile SPI_Typedef*)(SPI1_ADDRESS_BASE))

#endif