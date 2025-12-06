#include <stdio.h>
#include <GPIO.h>
#include <RCC.h>
#include <EXTI.h>
#include <TIM.h>
#include <ADC.h>
#include <UART.h>

uint16_t result = 0;

int main(){
	RCC_Config_Default();
	
	RCC_Enable_GPIOA();
	RCC_Enable_GPIOB();
	RCC_Enable_GPIOC();
	
	RCC_Enable_SYSCFG();
	
	RCC_Enable_TIM1();
	TIM1_Init();
	
	RCC_Enable_ADC1();
	GPIO_Config(GPIOC, PIN_0, MODE_IAN);
	ADC1_Channel0_Init();
	
	RCC_Enable_UART1();
	UART1_Init_9600();
	
	GPIO_Config(GPIOB, PIN_14, MODE_OPP);
	GPIO_Config(GPIOB, PIN_7, MODE_OPP);
	
	//EXTI13_Init();
	
	EXTI_Config(PIN_13, PORTC, MODE_RASING);
	
	while(1){
		/* Test Timer
		GPIO_Toggle_Pin(GPIOB, PIN_7);
		Delay_ms(1000);
		*/
		
		/* Test adc
		result = ADC1_Channel0_Read();
		*/
		
		/* Test TX function
		UART1_SendString("I am STM32F429ZI\n");
		Delay_ms(1000);
		*/
	}
}