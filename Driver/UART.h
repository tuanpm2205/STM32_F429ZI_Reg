#ifndef __UART_H
#define __UART_H

#include "TYPE.h"

typedef struct{
	__REG SR;
	__REG DR;
	__REG BRR;
	__REG CR1;
	__REG CR2;
	__REG CR3;
	__REG GTPR;
}UART_Typedef;

#define UART1_ADDRESS_BASE			0x40011000UL
#define UART1										((volatile UART_Typedef*)(UART1_ADDRESS_BASE))
	
void UART1_Init_9600(void);
void UART1_SendChar(char c);
void UART1_SendString(const char* str);
void USART1_IRQHandler(void);

#endif