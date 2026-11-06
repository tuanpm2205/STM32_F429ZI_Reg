#include "SPI.h"

void SPI1_Init_Master(void){
	GPIO_Config(SPI1_CSN_PORT, SPI1_CSN_PIN, MODE_OPP);
	GPIO_Config(SPI1_SCK_PORT, SPI1_SCK_PIN, MODE_APP);
	GPIO_Config(SPI1_MISO_PORT, SPI1_MISO_PIN, MODE_APP);
	GPIO_Config(SPI1_MOSI_PORT, SPI1_MOSI_PIN, MODE_APP);
	
	GPIOA->AFRL &= ~(0xFFF << 20);
	GPIOA->AFRL |= (0x555 << 20);
	
	SPI1->CR1 &= ~(0xFFFFFFFF);
	//SPI1->CR1 |= (0x14C << 0);
	SPI1-> CR1 |= (1 << 2); //Master
	SPI1-> CR1 |= (0b011 << 3); // APB2 = 36Mhz -> /4 = 8Mhz
	SPI1-> CR1 |= (1 << 9); //CSN software
	SPI1-> CR1 |= (1 << 8); // SSI
	SPI1-> CR1 |= (1 << 6); // Enable
	
	//NVIC_Enable_SPI1();
	SPI1_CS_SET
}

uint8_t SPI1_SendByte(uint8_t data){
	SPI1_CS_RESET
	while(!(SPI1->SR & (1 << 1)));
	SPI1->DR = data;
	while(!(SPI1->SR & (1 << 0)));
	uint32_t buffer = SPI1->DR;
	while((SPI1->SR & (1 << 7)));
	SPI1_CS_SET
	return (uint8_t)buffer;
}


