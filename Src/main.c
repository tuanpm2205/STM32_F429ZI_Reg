#include <stdio.h>
#include <GPIO.h>
#include <RCC.h>
#include <EXTI.h>
#include <TIM.h>
#include <ADC.h>
#include <UART.h>
#include <SPI.h>
#include <nrf24l01.h>
#include <string.h>


uint16_t result = 0;
uint16_t duty_led = 0;
uint8_t RxData[32];
volatile uint8_t nrf_irq = 0;
uint8_t data_control[5];



void EXTI9_5_IRQHandler(){
	if(EXTI->PR & (1 << 7)){
		nrf_irq = 1;
		EXTI->PR = (1 << 7);
	}
}

int main(){
	RCC_Config_Default();
	
	RCC_Enable_GPIOA();
	RCC_Enable_GPIOB();
	RCC_Enable_GPIOC();
	
	RCC_Enable_SYSCFG();
	
	RCC_Enable_TIM1();
	RCC_Enable_TIM8();
	RCC_Enable_SPI1();
	
	 
	TIM1_Init();
	TIM8_Init_PWM_1KHz();
	TIM8_Start_PWM();
	SPI1_Init_Master();
	
	//RCC_Enable_ADC1();
	//GPIO_Config(GPIOC, PIN_0, MODE_IAN);
	//ADC1_Channel0_Init();
	
	RCC_Enable_UART1();
	UART1_Init_9600();
	
	GPIO_Config(GPIOB, PIN_14, MODE_OPP);
	GPIO_Config(GPIOB, PIN_7, MODE_OPP);
	
	//EXTI13_Init();
	
	EXTI_Config(PIN_13, PORTC, MODE_RASING);
	EXTI_Config(PIN_7, PORTC, MODE_FALLING);
	Delay_ms(1000);
nrf_rx_init();
	while(1){
		for(uint32_t i =0; i < 1000000; i++);
		if (nrf_irq == 1){
			nrf_irq = 0;
			uint8_t status = nrf_get_status();
			if(status & (1 << 6)){
					nrf_read_payload(data_control, 5);
					for(uint8_t i = 0; i < 5; i++){
						UART1_SendChar(data_control[i]);
					}
			}
		}
		GPIO_Toggle_Pin(GPIOB, PIN_14);
		/* Test Timer
		GPIO_Toggle_Pin(GPIOB, PIN_7);
		Delay_ms(1000);
		*/
		
		/* Control led with PWM TIM8
		result = ADC1_Channel0_Read();
		duty_led = result*100/4095;
		TIM8_Update_Duty(duty_led);
		*/
		
		/* Test TX function
		UART1_SendString("I am STM32F429ZI\n");
		Delay_ms(1000);
		*/
		
		/* Test PWM
		for(int8_t i = 0; i <= 100; i++){
			TIM8_Update_Duty(i);
			Delay_ms(20);
		}
		for(int8_t i = 100; i >= 0; i--){
			TIM8_Update_Duty(i);
			Delay_ms(20);
		}
		*/
		
		
	}
}