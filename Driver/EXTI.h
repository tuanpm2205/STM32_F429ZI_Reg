/*
 * EXTI.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Tuan PM
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "TYPE.h"
#include "SYSCFG.h"
#include "ISER.h"
#include "GPIO.h"

typedef struct{
	__REG IMR;
	__REG EMR;
	__REG RTSR;
	__REG FTSR;
	__REG SWIER;
	__REG PR;
}EXTI_Typedef;

#define EXTI_ADDRESS_BASE				0x40013C00UL
#define EXTI							((volatile EXTI_Typedef*)EXTI_ADDRESS_BASE)

void EXTI13_Init(void);
void EXTI15_10_IRQHandler(void);

#endif /* EXTI_H_ */
