#include "ISER.h"

void NVIC_Enable_UART1(void){
	NVIC_ISER->ISER1 = (1 << 5);
}
void NVIC_Enable_EXTI0(void){
	NVIC_ISER->ISER0 = (1 << 6);
}
void NVIC_Enable_EXTI1(void){
	NVIC_ISER->ISER0 = (1 << 7);
}
void NVIC_Enable_EXTI2(void){
	NVIC_ISER->ISER0 = (1 << 8);
}
void NVIC_Enable_EXTI3(void){
	NVIC_ISER->ISER0 = (1 << 9);
}
void NVIC_Enable_EXTI4(void){
	NVIC_ISER->ISER0 = (1 << 10);
}
void NVIC_Enable_EXTI5_9(void){
	NVIC_ISER->ISER0 = (1 << 23);
}
void NVIC_Enable_EXTI10_15(void){
	NVIC_ISER->ISER1 = (1 << 8);
}