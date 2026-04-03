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
	SPI1-> CR1 |= (0b001 << 3); // APB2 = 36Mhz -> /4 = 8Mhz
	SPI1-> CR1 |= (1 << 9); //CSN software
	SPI1-> CR1 |= (1 << 8); // SSI
	SPI1-> CR1 |= (1 << 6); // Enable
	
	//NVIC_Enable_SPI1();
}

void SPI1_SendByte(uint8_t data){
	while(!(SPI1->SR & (1 << 1)));
	SPI1->DR = data;
}

void SPI1_Transmit(uint8_t *data, uint16_t Size){
	uint8_t dummy = 0xFF;
	while(Size--){
		SPI1_SendByte(*data);
		data++;
		while(!(SPI1->SR & (1 << 0))); // RXNE
		dummy = SPI1->DR;
	}
	while(SPI1->SR & (1 << 7));
}

void SPI1_Receive(uint8_t *data, uint16_t Size){
	uint8_t dummy = 0;
	while(Size--){
		SPI1_SendByte(dummy);
		while(!(SPI1->SR & (1 << 0))); // RXNE
		*data++ = SPI1->DR;
	}
	while(SPI1->SR & (1 << 7));
}
