#include <stdio.h>
#include <GPIO.h>
#include <RCC.h>
#include <EXTI.h>
#include <TIM.h>

void mDelay(volatile uint32_t time){
	while(time--);
}

int main(){
	RCC_Config_Default();
	RCC_Enable_GPIOB();
	RCC_Enable_GPIOC();
	RCC_Enable_SYSCFG();
	RCC_Enable_TIM1();
	TIM1_Init();
	GPIO_Config(GPIOB, PIN_14, MODE_OPP);
	GPIO_Config(GPIOB, PIN_7, MODE_OPP);
	//EXTI13_Init();
	
	EXTI_Config(PIN_13, PORTC, MODE_RASING);
	
	while(1){
		GPIO_Toggle_Pin(GPIOB, PIN_7);
		Delay_ms(1000);
	}
}