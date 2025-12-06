#include "TIM.h"

void TIM1_Init(void){
	TIM1->PSC = 71;
	TIM1->ARR = 65535;
	TIM1->EGR |= 1 << 0;
	TIM1->CR1 |= 1 << 0;
}

void Delay_us(uint16_t time){
	TIM1->CNT = 0;
	while(TIM1->CNT < time);
}

void Delay_ms(uint16_t time){
	while(time--){
		Delay_us(1000);
	}
}

void TIM8_Init_PWM_1KHz(void){
	GPIO_Config(GPIOC, PIN_6, MODE_APP);
	GPIOC->AFRL |= (0b11 << 24);
	
	TIM8->PSC = 719;
	TIM8->ARR = 100;
	
	TIM8->CCR1 = 50;    // Default 50%
	
	TIM8->CCMR1 |= (6 << 4);   // PWM mode 1 (OC1M = 110)
	TIM8->CCMR1 |= (1 << 3);   // OC1PE preload
	
	TIM8->CCER |= 1;          // CC1E enable output

	TIM8->BDTR |= (1 << 15);  // MOE = 1
	
	TIM8->CR1 |= (1 << 7);    // ARPE
	
	TIM8->EGR |= 1 << 0;
}
void TIM8_Start_PWM(void){
	TIM8->CR1 |= 1;           // CEN
}
void TIM8_Stop_PWM(void){
	TIM8->CR1 &= ~(1 << 0);   // CEN
}
void TIM8_Update_Duty(uint8_t duty){
	TIM8->CCR1 = duty;
}