#include <stdio.h>
#include <GPIO.h>
#include <RCC.h>
#include <EXTI.h>

void mDelay(volatile uint32_t time){
	while(time--);
}

int main(){
	RCC_Config_Default();
	RCC_Enable_GPIOB();
	RCC_Enable_GPIOC();
	RCC->APB2ENR |= (1 << 14);
	GPIO_Config(GPIOB, PIN_14, MODE_OPP);
	GPIO_Config(GPIOC, PIN_13, MODE_IPD);
	EXTI13_Init();
	while(1){
		GPIO_Toggle_Pin(GPIOB, PIN_14);
		mDelay(100000000);
	}
}