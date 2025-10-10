#include "RCC.h"

void RCC_Config_Default(void){
	RCC->CR |= (1 << 16);									//HSEON = 1
	while((RCC->CR & (1 << 17)) == 0);		// Check bit HSERDY
	
	RCC->PLLCFGR = 0;
	RCC->PLLCFGR |= (1 << 22);						// Select HSE , P = 0 -> Div 2
	RCC->PLLCFGR |= (4 << 0);							// M = 4
	RCC->PLLCFGR |= (72 << 6);						// N = 72
	RCC->PLLCFGR |= (3 << 24);						// Q = 3
	
	ACR &= ~(0b1111 << 0);
	ACR |= (2 << 0);
	
	RCC->CR |= (1 << 24);
	while((RCC->CR & (1 << 25)) == 0);
	
	RCC->CFGR &= ~(1 << 7);
	RCC->CFGR &= ~(0b111111 << 10);
	RCC->CFGR |= (1 << 12);
	RCC->CFGR |= (1 << 15);
	
	RCC->CFGR &= ~(0b11 << 0);
	RCC->CFGR |= (1 << 1);
	while((RCC->CFGR & 0b1100) != 0b1000);
}

void RCC_Config_168MHZ(void){
	RCC->CR |= (1 << 16);									//HSEON = 1
	while((RCC->CR & (1 << 17)) == 0);		// Check bit HSERDY
	
	RCC->PLLCFGR = 0;
	RCC->PLLCFGR |= (1 << 22);						// Select HSE , P = 0 -> Div 2
	RCC->PLLCFGR |= (4 << 0);							// M = 4
	RCC->PLLCFGR |= (168 << 6);						// N = 72
	RCC->PLLCFGR |= (7 << 24);						// Q = 3
	
	ACR &= ~(0b1111 << 0);
	ACR |= (5 << 0);
	
	RCC->CR |= (1 << 24);
	while((RCC->CR & (1 << 25)) == 0);
	
	RCC->CFGR = 0;
	RCC->CFGR &= ~(1 << 7);								// HCLK to AHB div 1
	RCC->CFGR &= ~(0b111111 << 10);
	RCC->CFGR |= (0b101 << 10);								// APB1 div 4
	RCC->CFGR |= (1 << 15);								// APB2 div 2
	
	RCC->CFGR &= ~(0b11 << 0);
	RCC->CFGR |= (1 << 1);
	while((RCC->CFGR & 0b1100) != 0b1000);
}