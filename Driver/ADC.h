#ifndef __ADC_H
#define __ADC_H

#include "TYPE.h"

typedef struct{
	__REG SR;
	__REG CR1;
	__REG CR2;
	__REG SMPR1;
	__REG SMPR2;
	__REG JOFR1;
	__REG JOFR2;
	__REG JOFR3;
	__REG JOFR4;
	__REG HTR;
	__REG LTR;
	__REG SQR1;
	__REG SQR2;
	__REG SQR3;
	__REG JSQR;
	__REG JDR1;
	__REG JDR2;
	__REG JDR3;
	__REG JDR4;
	__REG DR;
	__REG CSR;
	__REG CCR;
	__REG CDR;
}ADC_Typedef;

#define ADC1_ADDRESS_BASE						0x40012000UL
#define ADC1												((volatile ADC_Typedef*)(ADC1_ADDRESS_BASE))

void ADC_Init(void);

#endif