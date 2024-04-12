#include "coil.h"

Coil::Coil(GPIO_TypeDef * gpio, uint8_t pin) {
	if(pin > 15){
		pin = 0;
	}
	
	this->gpio = gpio;
	this->pin = pin;
	
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
		gpio->CRL |= (1 << (4 * pin));
	} else {
		gpio->CRH |= (0x01 << (4 * pin - 32));
	}
}

uint8_t Coil::isActive(){
	return (gpio->ODR & (1 << pin)) > 0;
}
		
void Coil::setPin(){
	gpio->BSRR |= (1 << pin);
}
		
void Coil::resetPin(){
	gpio->BRR |= (1 << pin);
}

void Coil::setValue(uint8_t value){
	if(value){
		setPin();
		return;
	}
	resetPin();
}

void Coil::togglePin(){
	setValue(!isActive());
}

Coil& Coil::operator=(int8_t value)
{
  setValue(value);
  return *this;
}