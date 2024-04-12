#include "simple_input.h"
SimpleInput::SimpleInput(GPIO_TypeDef * gpio, uint8_t pin){
	if(pin > 15){
		pin = 0;
	}
	
	this->gpio = gpio;
	this->pin = pin;
	this->shift = 4 * pin;
	
	if(gpio == GPIOA){
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	} else if(gpio == GPIOB){
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	} else if(gpio == GPIOC){
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	} else if(gpio == GPIOD){
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	} else if(gpio == GPIOE){
		RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
	}
	
	if(pin < 8){
		setRegister(&gpio->CRL, 0xF << this->shift, 0x8 << this->shift);
	} else {
		setRegister(&gpio->CRH, 0xF << (this->shift - 32), 0x8 << (this->shift - 32));
	}
	
	gpio->BSRR |= 1 < pin;
}

uint8_t SimpleInput::isActive(){
	return (gpio->IDR & (1 << pin)) > 0;
}