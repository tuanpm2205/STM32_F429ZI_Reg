#include "EXTI.h"

void EXTI15_10_IRQHandler(){
	if(EXTI->PR & (1 << 13)){
		GPIO_Toggle_Pin(GPIOB, PIN_14);
		EXTI->PR = (1 << 13);
	}
}
void EXTI_Config(uint16_t PIN, uint8_t PORTx, uint8_t Mode){
	uint8_t PUPD = (Mode == MODE_RASING) ? MODE_IPD : MODE_IPU;
	// Pull-up or Pull-down
	switch(PORTx){
		case PORTA:
			GPIO_Config(GPIOA, PIN, PUPD);
			break;
		case PORTB:
			GPIO_Config(GPIOB, PIN, PUPD);
			break;
		case PORTC:
			GPIO_Config(GPIOC, PIN, PUPD);
			break;
		case PORTD:
			GPIO_Config(GPIOD, PIN, PUPD);
			break;
		case PORTE:
			GPIO_Config(GPIOE, PIN, PUPD);
			break;
		case PORTF:
			GPIO_Config(GPIOF, PIN, PUPD);
			break;
		case PORTG:
			GPIO_Config(GPIOG, PIN, PUPD);
			break;
		case PORTH:
			GPIO_Config(GPIOH, PIN, PUPD);
			break;
	}
	for(uint8_t i=0; i < 16; i++){
		if(PIN & (1 << i)){
			// Enable line interrupt
			EXTI->IMR |= (1 << i);
			// Port interrupt
			switch((1 << i)){
				case PIN_0:
				case PIN_1:
				case PIN_2:
				case PIN_3:
					SYSCFG->EXTICR1 &= ~(0b1111 << (i%4)*4);
					SYSCFG->EXTICR1 |= (PORTx << (i%4)*4);
					break;
				case PIN_4:
				case PIN_5:
				case PIN_6:
				case PIN_7:
					SYSCFG->EXTICR2 &= ~(0b1111 << (i%4)*4);
					SYSCFG->EXTICR2 |= (PORTx << (i%4)*4);
					break;
				case PIN_8:
				case PIN_9:
				case PIN_10:
				case PIN_11:
					SYSCFG->EXTICR3 &= ~(0b1111 << (i%4)*4);
					SYSCFG->EXTICR3 |= (PORTx << (i%4)*4);
					break;
				case PIN_12:
				case PIN_13:
				case PIN_14:
				case PIN_15:
					SYSCFG->EXTICR4 &= ~(0b1111 << (i%4)*4);
					SYSCFG->EXTICR4 |= (PORTx << (i%4)*4);
					break;
			}
			switch(Mode){
				case MODE_RASING:
					EXTI->RTSR |= (1<<i);
					break;
				case MODE_FALLING:
					EXTI->FTSR |= (1<<i);
					break;
			}
			switch((1 << i)){
				case PIN_0:
					NVIC_Enable_EXTI0();
					break;
				case PIN_1:
					NVIC_Enable_EXTI1();
					break;
				case PIN_2:
					NVIC_Enable_EXTI2();
					break;
				case PIN_3:
					NVIC_Enable_EXTI3();
					break;
				case PIN_4:
					NVIC_Enable_EXTI4();
					break;
				case PIN_5:
				case PIN_6:
				case PIN_7:
				case PIN_8:
				case PIN_9:
					NVIC_Enable_EXTI5_9();
					break;
				case PIN_10:
				case PIN_11:
				case PIN_12:
				case PIN_13:
				case PIN_14:
				case PIN_15:
					NVIC_Enable_EXTI10_15();
					break;
			}
		}
	}
}