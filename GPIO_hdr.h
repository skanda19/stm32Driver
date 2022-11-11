#ifndef Gpio_hdr
#define Gpio_hdr

#include "stm32f407xx.h"

// STATES
#define LOW				0
#define HIGH			1

// 	PORTS
#define PORTA			GPIOA
#define PORTB			GPIOB
#define PORTC			GPIOC
#define PORTD			GPIOD
#define PORTE			GPIOE
#define PORTF			GPIOF
#define PORTG			GPIOG
#define PORTH			GPIOH
#define PORTI			GPIOI



//	MODE
#define INPUT_MODE												((uint32_t) 0x0)								//INPUT / RESET STATE
#define OUTPUT_MODE												((uint32_t) 0x1)								//GENERAL PURPOSE OUTPUT MODE
#define	ALT_FUNCTION_MODE										((uint32_t)	0x2)								//ALTERNATE FUNCTION MODE
#define ANALOG_MODE												((uint32_t) 0x3)								//ANALOG MODE+
/***************************************************************************************************************************************************************/
#define INTERRUPT_RT											((uint32_t) 0x4)								//INTERRUPT RISING EDGE
#define INTERRUPT_FT											((uint32_t) 0x5)								//INTRRUPT FALLING EDGE
#define INTERRUPT_RT_FT											((uint32_t) 0x6)								//INTERRUPT RISING_FALLING_EDGE


//	PORT ENABLE
#define GPIO_CLOCK_ENABLE_PORTA									(RCC->AHB1ENR |= (0x01 << 0))					//ENABLES CLOCK FOR PORT A
#define GPIO_CLOCK_ENABLE_PORTB									(RCC->AHB1ENR |= (0x01 << 1))					//ENABLES CLOCK FOR PORT B
#define GPIO_CLOCK_ENABLE_PORTC									(RCC->AHB1ENR |= (0x01 << 2))					//ENABLES CLOCK FOR PORT C
#define GPIO_CLOCK_ENABLE_PORTD									(RCC->AHB1ENR |= (0x01 << 3))					//ENABLES CLOCK FOR PORT D
#define GPIO_CLOCK_ENABLE_PORTE									(RCC->AHB1ENR |= (0x01 << 4))					//ENABLES CLOCK FOR PORT E
#define GPIO_CLOCK_ENABLE_PORTF									(RCC->AHB1ENR |= (0x01 << 5))					//ENABLES CLOCK FOR PORT F
#define GPIO_CLOCK_ENABLE_PORTG									(RCC->AHB1ENR |= (0x01 << 6))					//ENABLES CLOCK FOR PORT G
#define GPIO_CLOCK_ENABLE_PORTH									(RCC->AHB1ENR |= (0x01 << 7))					//ENABLES CLOCK FOR PORT H
#define GPIO_CLOCK_ENABLE_PORTI									(RCC->AHB1ENR |= (0x01 << 8))					//ENABLES CLOCK FOR PORT I

/*
//		IRQ INTERRUPT REQUEST									EXTIx
#define IRQ_exti0												EXTI0_IRQn										//priority = 6
#define IRQ_exti1												EXTI1_IRQn										//priority = 7
#define IRQ_exti2												EXTI2_IRQn										//priority = 8
#define IRQ_exti3												EXTI3_IRQn										//priority = 9
#define IRQ_exti4												EXTI4_IRQn										//priority = 10
#define IRQ_exti9_5												EXTI9_5_IRQn									//priority = 23
#define IRQ_exti15_10											EXTI15_10_IRQn									//priority = 40
*/

//	SYS_CONFIG ENABLE
#define SYS_CFG_ENABLE											(RCC->APB2ENR |= (HIGH << 14))					//ENABLES SYSCFG FOR INTERRUPTS

// OUTPUT SPEED
#define LOW_SPEED												(0x00)
#define MEDIUM_SPEED 											(0x01)
#define HIGH_SPEED												(0x10)
#define VERY_HIGH_SPEED											(0x11)

//CONFIGURATION
typedef struct{

		GPIO_TypeDef *port;

		uint32_t pin;
		uint32_t mode;
		uint32_t mode_type;
		uint32_t pull;
		uint32_t speed;
		uint32_t alt_func;

}GPIO_TYPE;

typedef struct{

	EXTI_TypeDef *pEXTIxIntConfig;

	uint32_t imr;
	uint32_t emr;
	uint32_t rtsr;
	uint32_t ftsr;
	uint32_t swier;
	uint32_t pr;

}EXTI_Config;

typedef struct {
	//SYSCFG_TypeDef 	*pSYSConfig;

	uint32_t memrmp;
	uint32_t pmc;
	uint32_t exticr[4];
	uint32_t cmpcr;

}SYS_CFG;


//FUNCTIONS PROTOTYPES

//GPIO CONFIGURATION

void gpioInit(GPIO_TYPE gpio_type);
static void config_pin (GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);
static void config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode);
//void EXTIConfig(GPIO_TYPE *port,EXTI_Config *EXTI_PD10, uint32_t pinNumber);
//void sysIntConfig(GPIO_TYPE gpio_type, SYSCFG_TypeDef *pSysConfig, EXTI_TypeDef *pEXTIxIntConfig);



//USER FUNCTIONS
volatile void delay(uint32_t time);
void pinWrite (GPIO_TypeDef *port, uint32_t pinNumber);


#endif
