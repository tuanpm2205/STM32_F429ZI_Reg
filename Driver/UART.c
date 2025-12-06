#include "UART.h"
#include "GPIO.h"

void UART1_Init_9600(void){
	GPIO_Config(GPIOA, PIN_9, MODE_APP);
	GPIO_Config(GPIOA, PIN_10, MODE_APP);
	GPIOA->AFRH |= (0x7 << 4);
	GPIOA->AFRH |= (0x7 << 8);
	
	UART1->BRR = 0xEA6; // Clk = 72MHz, OVER8 = 0, Baudrate = 9600
	
	UART1->CR1 |= (1 << 13);
	UART1->CR1 |= (0b11 << 2);
}

void UART1_SendChar(char c){
	while(!(UART1->SR & (1 << 7)));
	UART1->DR = c;
}

void UART1_SendString(const char* str){
	while(*str){
		UART1_SendChar(*str++);
	}
}

void USART1_IRQHandler(void);