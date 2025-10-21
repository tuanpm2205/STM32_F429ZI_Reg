/*
 * EXTI.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Tuan PM
 */


#include "EXTI.h"

void EXTI13_Init(){
	SYSCFG->EXTICR4 &= ~(0b1111 << 4);
	SYSCFG->EXTICR4 |= (1 << 5);
	EXTI->IMR |= (1 << 13);
	EXTI->RTSR |= (1 << 13);
	NVIC_ISER->ISER1 = (1 << 8);
}
void EXTI15_10_IRQHandler(){
	GPIO_Toggle_Pin(GPIOB, PIN_14);
	EXTI->PR = (1 << 13);
}
