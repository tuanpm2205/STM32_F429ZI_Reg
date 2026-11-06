#ifndef __SPI_H
#define __SPI_H

#include "TYPE.h"
#include "GPIO.h"
#include "ISER.h"

#define SPI1_SCK_PORT GPIOA
#define SPI1_SCK_PIN PIN_5

#define SPI1_MISO_PORT GPIOA
#define SPI1_MISO_PIN PIN_6

#define SPI1_MOSI_PORT GPIOA
#define SPI1_MOSI_PIN PIN_7


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
	

void SPI1_Init_Master(void);
void SPI1_SendByte(uint8_t *data, uint8_t* buffer);
void SPI1_Transmit(uint8_t *data, uint16_t Size);
void SPI1_Receive(uint8_t *data, uint16_t Size);

#endif