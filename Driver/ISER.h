#ifndef __ISER_H
#define __ISER_H

#include "TYPE.h"

typedef struct{
	__REG ISER0;
	__REG ISER1;
	__REG ISER2;
	__REG ISER3;
	__REG ISER4;
	__REG ISER5;
	__REG ISER6;
	__REG ISER7;
}NVIC_ISER_Typedef;


#define NVIC_ISER			((volatile NVIC_ISER_Typedef*)0xE000E100UL)
	
void NVIC_Enable_UART1(void);
void NVIC_Enable_EXTI0(void);
void NVIC_Enable_EXTI1(void);
void NVIC_Enable_EXTI2(void);
void NVIC_Enable_EXTI3(void);
void NVIC_Enable_EXTI4(void);
void NVIC_Enable_EXTI5_9(void);
void NVIC_Enable_EXTI10_15(void);

#endif
