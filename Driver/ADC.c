#include "ADC.h"
#include "TIM.h"

void ADC1_Channel0_Init(void){
	ADC1->SMPR2 &= ~(0b111 << 0);
	ADC1->SMPR2 |= (0b11 << 0); // 56 cycles
	
	//PC0 -> Channel 10
	ADC1->SQR3 = (10 << 0);
	ADC1->SQR1 = 0;
	
	ADC1->CR2 |= (1 << 1);
	
	//On ADC
	ADC1->CR2 |= (1 << 0);
	
	ADC1->CR2 |= (1 << 30); // Start
}

uint16_t ADC1_Channel0_Read(void){
	while(!(ADC1->SR & 0x2));
	return (uint16_t)(ADC1->DR & 0xFFFF);
}