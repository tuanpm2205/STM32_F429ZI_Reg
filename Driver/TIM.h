#ifndef __TIM_H
#define __TIM_H

#include "TYPE.h"
#include "GPIO.h"

// Just develop for TIM1

typedef struct{
	__REG CR1;
	__REG CR2;
	__REG SMCR;
	__REG DIER;
	__REG SR;
	__REG EGR;
	__REG CCMR1;
	__REG CCMR2;
	__REG CCER;
	__REG CNT;
	__REG PSC;
	__REG ARR;
	__REG RCR;
	__REG CCR1;
	__REG CCR2;
	__REG CCR3;
	__REG CCR4;
	__REG BDTR;
	__REG DCR;
	__REG DMAR;
}TIM1_Typedef;

#define TIM1_ADDRESS_BASE				0x40010000UL
#define TIM1										((volatile TIM1_Typedef*)TIM1_ADDRESS_BASE)
	
#define TIM8_ADDRESS_BASE				0x40010400UL
#define TIM8										((volatile TIM1_Typedef*)TIM8_ADDRESS_BASE)
	

void TIM1_Init(void);

void TIM8_Init_PWM_1KHz(void);
void TIM8_Start_PWM(void);
void TIM8_Stop_PWM(void);
void TIM8_Update_Duty(uint8_t duty);

void Delay_ms(uint16_t time);	//Clock 72MHz
void Delay_us(uint16_t time); //Clock 72MHz

#endif