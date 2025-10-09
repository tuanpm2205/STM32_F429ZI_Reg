#ifndef __RCC_H
#define __RCC_H

#include <TYPE.h>

typedef struct{
	__REG		CR;
	__REG 	PLLCFGR;
	__REG 	CFGR;
	__REG 	CIR;
	__REG 	AHB1RSTR;
	__REG 	AHB2RSTR;
	__REG 	AHB3RSTR;
	__REG 	Reserved1;
	__REG 	APB1RSTR;
	__REG 	APB2RSTR;
	__REG 	Reserved2;
	__REG 	Reserved3;
	__REG 	AHB1ENR;
	__REG 	AHB2ENR;
	__REG 	AHB3ENR;
	__REG 	Reserved4;
	__REG 	APB1ENR;
	__REG 	APB2ENR;
	__REG 	Reserved5;
	__REG 	Reserved6;
	__REG 	AHB1LPENR;
	__REG 	AHB2LPENR;
	__REG 	AHB3LPENR;
	__REG 	Reserved7;
	__REG 	APB1LPENR;
	__REG 	APB2LPENR;
	__REG 	Reserved8;
	__REG 	Reserved9;
	__REG 	BDCR;
	__REG 	CSR;
	__REG 	Reserved10;
	__REG 	Reserved11;
	__REG 	SSCGR;
	__REG 	PLLI2SCFGR;
	__REG 	PLLSAICFGR;
	__REG 	DCKCFGR;
}RCC_Typedef;


#define RCC_ADDRESS_BASE						0x40023800UL
#define RCC													((volatile RCC_Typedef*)RCC_ADDRESS_BASE)
	



#endif