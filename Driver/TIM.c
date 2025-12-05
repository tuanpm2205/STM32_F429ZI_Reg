#include "TIM.h"

void TIM1_Init(void){
	TIM1->PSC = 71;
	TIM1->ARR = 65535;
	TIM1->EGR |= 1 << 0;
	TIM1->CR1 |= 1 << 0;
}

void Delay_us(uint32_t time){
	TIM1->CNT = 0;
	while(TIM1->CNT < time);
}

void Delay_ms(uint32_t time){
	while(time--){
		Delay_us(1000);
	}
}