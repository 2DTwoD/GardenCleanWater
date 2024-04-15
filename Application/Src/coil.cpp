#include "coil.h"

Coil::Coil(GPIO_TypeDef * gpio, uint8_t pin): GPIOcommon(gpio, pin) {
	if(pin < 8){			
		gpio->CRL |= (0x01 << (4 * pin));
	} else {
		gpio->CRH |= (0x01 << (4 * pin - 32));
	}
}

bool Coil::isActive(){
	return (gpio->ODR & (1 << pin)) > 0;
}
		
void Coil::setPin(){
	gpio->BSRR |= (1 << pin);
}
		
void Coil::resetPin(){
	gpio->BRR |= (1 << pin);
}

void Coil::setValue(bool value){
	if(value){
		setPin();
		return;
	}
	resetPin();
}

void Coil::togglePin(){
	setValue(!isActive());
}

Coil& Coil::operator=(bool value)
{
  setValue(value);
  return *this;
}