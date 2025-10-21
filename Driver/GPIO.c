#include "GPIO.h"

void GPIO_Config(volatile GPIO_Typedef *GPIOx, uint16_t GPIO_Pin, uint8_t Mode){

	uint32_t Moder = 0;
	uint32_t Otyper = 0;
	uint32_t Ospeedr = 0;   // Default: Max speed
	uint32_t Pupdr = 0; 

	switch(Mode){
		case MODE_OPP:
			Moder = 0b01;
			Otyper = 0;
			Ospeedr = 0b11;
			Pupdr = 0b00;
			break;
		case MODE_OOD:
			Moder = 0b01;
			Otyper = 1;
			Ospeedr = 0b11;
			Pupdr = 0b00;
			break;
		case MODE_APP:
			Moder = 0b10;
			Otyper = 0;
			Ospeedr = 0b11;
			Pupdr = 0b00;
			break;
		case MODE_AOD:
			Moder = 0b10;
			Otyper = 1;
			Ospeedr = 0b11;
			Pupdr = 0b00;
			break;
		case MODE_IFL:
			Moder = 0b00;
			Pupdr = 0b00;
			break;
		case MODE_IAN:
			Moder = 0b11;
			Pupdr = 0b00;
			break;
		case MODE_IPU:
			Moder = 0b00;
			Pupdr = 0b01;
			break;
		case MODE_IPD:
			Moder = 0b00;
			Pupdr = 0b10;
	}

	for(uint8_t i = 0; i < 16; i++){
		if(((1 << i) & GPIO_Pin)){
			GPIOx->MODER &= ~((uint32_t)0b11 << (i*2));
			GPIOx->OTYPER &= ~((uint32_t)0b1 << i);
			GPIOx->OSPEEDR &= ~((uint32_t)0b11 << (i*2));
			GPIOx->PUPDR &= ~((uint32_t)0b11 << (i*2));
			
			GPIOx->MODER |= (Moder << (i*2));
			GPIOx->OTYPER |= (Otyper << i);
			GPIOx->OSPEEDR |= (Ospeedr << (i*2));
			GPIOx->PUPDR |= (Pupdr << (i*2));
		}
	}
}

void GPIO_Write_Pin(volatile GPIO_Typedef *GPIOx, uint16_t GPIO_Pin, uint8_t State){
	if(State){
		GPIOx->BSRR = GPIO_Pin;
	}else{
		GPIOx->BSRR = ((uint32_t)GPIO_Pin << 16);
	}
}

uint8_t GPIO_Read_Pin(volatile GPIO_Typedef *GPIOx, uint16_t GPIO_Pin){
	if((GPIOx->IDR & (uint32_t)GPIO_Pin) != 0){
		return 1;
	}else{
		return 0;
	}
}

void GPIO_Toggle_Pin(volatile GPIO_Typedef *GPIOx, uint16_t GPIO_Pin){
	for(uint8_t i = 0; i < 16; i++){
		if(((1 << i) & GPIO_Pin)){
			if((GPIOx->ODR & (uint32_t)(1 << i)) != 0){
				GPIOx->BSRR = ((uint32_t)1 << (i + 16));
			}else{
				GPIOx->BSRR = (1 << i);
			}
		}
	}
}