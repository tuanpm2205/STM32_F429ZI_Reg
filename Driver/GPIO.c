#include "GPIO.h"

void GPIO_Config(GPIO_Typedef *GPIOx, uint8_t GPIO_Pin, uint8_t Mode){
	uint8_t Pin = 0;
	for(uint8_t i = 0; i < 16; i++){
		if(((1 << i) & GPIO_Pin)){
			Pin = i;
		}
	}
	
}