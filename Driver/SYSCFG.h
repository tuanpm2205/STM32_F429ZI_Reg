/*
 * SYSCFG.h
 *
 *  Created on: Oct 10, 2025
 *      Author: phamm
 */

#ifndef SYSCFG_H_
#define SYSCFG_H_

#include "TYPE.h"

typedef struct{
	__REG MEMRMP;
	__REG PMC;
	__REG EXTICR1;
	__REG EXTICR2;
	__REG EXTICR3;
	__REG EXTICR4;
	__REG CMPCR;
}SYSCFG_Typedef;

#define SYSCFG_ADDRESS_BASE				0x40013800UL
#define SYSCFG							((volatile SYSCFG_Typedef*)SYSCFG_ADDRESS_BASE)

#endif /* SYSCFG_H_ */
