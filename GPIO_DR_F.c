#include <stdlib.h>
#include <stdio.h>
#include "stm32f407xx.h"
#include "GPIO_hdr.h"


uint32_t INTPINPOS[16] = {
		(0x00),							//Pin 0
		(0x01),							//Pin 1
		(0x02),							//Pin 2
		(0x03),							//Pin 3
		(0x04),							//Pin 4
		(0x05),							//Pin 5
		(0x06),							//Pin 6
		(0x07),							//Pin 7
		(0x08),							//Pin 8
		(0x09),							//Pin 9
		(0x0A),							//Pin 10
		(0x0B),							//Pin 11
		(0x0C),							//Pin 12
		(0x0D),							//Pin 13
		(0x0E),							//Pin 14
		(0x0F),							//Pin 15
};

void gpioInit(GPIO_TYPE gpio_type){
	if(gpio_type.port== PORTA)
			GPIO_CLOCK_ENABLE_PORTA;
	if(gpio_type.port== PORTB)
			GPIO_CLOCK_ENABLE_PORTB;
	if(gpio_type.port== PORTC)
			GPIO_CLOCK_ENABLE_PORTC;
	if(gpio_type.port== PORTD)
			GPIO_CLOCK_ENABLE_PORTD;
	if(gpio_type.port== PORTE)
			GPIO_CLOCK_ENABLE_PORTE;
	if(gpio_type.port== PORTF)
			GPIO_CLOCK_ENABLE_PORTF;
	if(gpio_type.port== PORTG)
			GPIO_CLOCK_ENABLE_PORTG;
	if(gpio_type.port== PORTH)
			GPIO_CLOCK_ENABLE_PORTH;
	if(gpio_type.port== PORTI)
			GPIO_CLOCK_ENABLE_PORTI;

	config_pin (gpio_type.port, gpio_type.pin, gpio_type.mode_type);
	config_pin_speed(gpio_type.port, gpio_type.pin, gpio_type.speed, gpio_type.mode);


}

static void config_pin (GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type){

	switch(mode_type){
	case INPUT_MODE:
		port->MODER &= ~( 0x3 << pinNumber);
		break;
	case OUTPUT_MODE:
		port->MODER |= ( 0x1 << pinNumber*2);
		break;
	case ALT_FUNCTION_MODE:
		port->MODER |= ( 0x2 << pinNumber);
		break;
	case ANALOG_MODE:
		port->MODER |= ( 0x3 << pinNumber);
		break;
	case INTERRUPT_FT:
		port->MODER &= ~(0x3 << pinNumber);
		SYS_CFG_ENABLE;
		EXTI->FTSR |= (HIGH << pinNumber);
		EXTI->RTSR &= ~(HIGH << pinNumber);
		EXTI->IMR |= (HIGH << pinNumber);
		break;
	case INTERRUPT_RT:
		port->MODER &= ~(0x3 << pinNumber);
		SYS_CFG_ENABLE;
		EXTI->RTSR |= (HIGH << pinNumber);
		EXTI->FTSR &= ~(HIGH << pinNumber);
		EXTI->IMR |= (HIGH << pinNumber);
		break;
	case INTERRUPT_RT_FT:
		port->MODER &= ~(0x3 << pinNumber);
		SYS_CFG_ENABLE;
		EXTI->FTSR |= (HIGH << pinNumber);
		EXTI->RTSR |= (HIGH << pinNumber);
		EXTI->IMR |= (HIGH << pinNumber);
		break;
	}

};

static void config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode){
	if(mode == OUTPUT_MODE){
		switch(pinSpeed){
		case LOW_SPEED:
			port->OSPEEDR &= ( LOW_SPEED << pinNumber*2);
			break;
		case MEDIUM_SPEED:
			port->OSPEEDR |= (MEDIUM_SPEED << pinNumber*2);
			break;
		case HIGH_SPEED:
			port->OSPEEDR |= (HIGH_SPEED << pinNumber*2);
			break;
		case VERY_HIGH_SPEED:
			port->OSPEEDR |= (VERY_HIGH_SPEED << pinNumber*2);
		break;
		}
	}
}

/*void sysIntConfig(GPIO_TYPE gpio_type, SYSCFG_TypeDef *pSysConfig, EXTI_TypeDef *pEXTIxIntConfig){
	uint32_t temp1 = 0, temp2 = 0, temp3;
	temp1 = gpio_type.pin / 4;			//	helps to determine witch of the EXTICRx is the one that has to be configured.
	temp2 = gpio_type.pin % 4;			// 	helps to determine witch section of the register will be configured.

		if(gpio_type.port == GPIOA)		temp3 = 0x0;
		if(gpio_type.port == GPIOB)		temp3 = 0x1;
		if(gpio_type.port == GPIOC)		temp3 = 0x2;
		if(gpio_type.port == GPIOD)		temp3 = 0x3;
		if(gpio_type.port == GPIOE)		temp3 = 0x4;
		if(gpio_type.port == GPIOF)		temp3 = 0x5;
		if(gpio_type.port == GPIOG)		temp3 = 0x6;
		if(gpio_type.port == GPIOH)		temp3 = 0x7;
		if(gpio_type.port == GPIOI)		temp3 = 0x8;

	if(temp1 == 0)		pSysConfig->EXTICR[0] |= (temp3 << temp2);							// 0 pin to 3 pin
	if(temp1 == 1)		pSysConfig->EXTICR[1] |= (temp3 << (temp2*4));						// 4 pin to 7 pin
	if(temp1 == 2)		pSysConfig->EXTICR[2] |= (temp3 << (temp2*4));						// 8 pin to 11 pin
	if(temp1 == 3)		pSysConfig->EXTICR[3] |= (temp3 << (temp2*3));						// 12 pin to 15 pin


}*/





volatile void DELAY(uint16_t time){
	for(int i = 0; i < time; i++){}
}

void pinWrite (GPIO_TypeDef *port, uint32_t pinNumber){
	port->ODR ^= (HIGH << pinNumber);

}





