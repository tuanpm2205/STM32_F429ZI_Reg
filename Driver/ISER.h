/*
 * ISER.h
 *
 *  Created on: Oct 21, 2025
 *      Author: phamm
 */

#ifndef ISER_H_
#define ISER_H_

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

#endif /* ISER_H_ */
