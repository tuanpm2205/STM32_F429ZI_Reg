#ifndef __GPIO_H
#define __GPIO_H

#include "TYPE.h"

#define PIN_0 			(uint16_t)0x0001
#define PIN_1 			(uint16_t)0x0002
#define PIN_2 			(uint16_t)0x0004
#define PIN_3 			(uint16_t)0x0008
#define PIN_4 			(uint16_t)0x0010
#define PIN_5 			(uint16_t)0x0020
#define PIN_6 			(uint16_t)0x0040
#define PIN_7 			(uint16_t)0x0080
#define PIN_8	 			(uint16_t)0x0100
#define PIN_9 			(uint16_t)0x0200
#define PIN_10 			(uint16_t)0x0400
#define PIN_11 			(uint16_t)0x0800
#define PIN_12 			(uint16_t)0x1000
#define PIN_13 			(uint16_t)0x2000
#define PIN_14 			(uint16_t)0x4000
#define PIN_15 			(uint16_t)0x8000

#define MODE_OPP 		0x01			//Output push-pull
#define MODE_OOD		0x02			//Output open-drain
#define MODE_APP		0x03			//Alternate push-pull
#define MODE_AOD		0x04			//Alternatr open-drain
#define MODE_IFL		0x05 			//Input floating
#define MODE_IAN		0x06			//Input analog
#define MODE_IPU		0x07			//Input pull-up
#define MODE_IPD		0x08			//Input pull-down

typedef struct {
	__REG		MODER;
	__REG		OTYPER;
	__REG		OSPEEDR;
	__REG		PUPDR;
	__REG		IDR;
	__REG		ODR;
	__REG		BSRR;
	__REG		LCKR;
	__REG		AFRL;
	__REG		AFRH;
}GPIO_Typedef;

#define GPIOA_ADDRESS_BASE 						0x40020000UL
#define GPIOB_ADDRESS_BASE 						0x40020400UL
#define GPIOC_ADDRESS_BASE 						0x40020800UL
#define GPIOD_ADDRESS_BASE 						0x40020C00UL
#define GPIOE_ADDRESS_BASE 						0x40021000UL
#define GPIOF_ADDRESS_BASE 						0x40021400UL
#define GPIOG_ADDRESS_BASE 						0x40021800UL
#define GPIOH_ADDRESS_BASE 						0x40021C00UL

#define GPIOA													((volatile GPIO_Typedef*)GPIOA_ADDRESS_BASE)
#define GPIOB													((volatile GPIO_Typedef*)GPIOB_ADDRESS_BASE)
#define GPIOC													((volatile GPIO_Typedef*)GPIOC_ADDRESS_BASE)
#define GPIOD													((volatile GPIO_Typedef*)GPIOD_ADDRESS_BASE)
#define GPIOE													((volatile GPIO_Typedef*)GPIOE_ADDRESS_BASE)
#define GPIOF													((volatile GPIO_Typedef*)GPIOF_ADDRESS_BASE)
#define GPIOG													((volatile GPIO_Typedef*)GPIOG_ADDRESS_BASE)
#define GPIOH													((volatile GPIO_Typedef*)GPIOH_ADDRESS_BASE)

void GPIO_Config(GPIO_Typedef *GPIOx, uint16_t GPIO_Pin, uint8_t Mode);
void GPIO_Write_Pin(GPIO_Typedef *GPIOx, uint16_t GPIO_Pin, uint8_t State);
uint8_t GPIO_Read_Pin(GPIO_Typedef *GPIOx, uint16_t GPIO_Pin);
void GPIO_Toggle_Pin(GPIO_Typedef *GPIOx, uint16_t GPIO_Pin);

#endif