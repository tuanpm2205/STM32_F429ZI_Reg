#ifndef __GPIO_H
#define __GPIO_H

#include "TYPE.h"

#define PIN_0 			0x00000001UL
#define PIN_1 			0x00000002UL
#define PIN_2 			0x00000004UL
#define PIN_3 			0x00000008UL
#define PIN_4 			0x00000010UL
#define PIN_5 			0x00000020UL
#define PIN_6 			0x00000040UL
#define PIN_7 			0x00000080UL
#define PIN_8	 			0x00000100UL
#define PIN_9 			0x00000200UL
#define PIN_10 			0x00000400UL
#define PIN_11 			0x00000800UL
#define PIN_12 			0x00001000UL
#define PIN_13 			0x00002000UL
#define PIN_14 			0x00004000UL
#define PIN_15 			0x00008000UL

#define MODE_OPP 		0x01; //Output push-pull
#define MODE_OOD		0x02;	//Output open-drain
#define MODE_APP		0x03; //Alternate push-pull
#define MODE_AOD		0x04; //Alternatr open-drain
#define MODE_IFL		0x05; //Input floating
#define MODE_IAN		0x06; //Input analog
#define MODE_IPU		0x07; //Input pull-up
#define MODE_IPD		0x08; //Input pull-down

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

void GPIO_Config(GPIO_Typedef *GPIOx, uint8_t GPIO_Pin, uint8_t Mode);
void GPIO_Write_Pin(GPIO_Typedef *GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_Read_Pin(GPIO_Typedef *GPIOx, uint8_t GPIO_Pin);
void GPIO_Toggle_Pin(GPIO_Typedef *GPIOx, uint8_t GPIO_Pin);

#endif