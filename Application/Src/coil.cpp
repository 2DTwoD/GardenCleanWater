#include "coil.h"

bool ProgrammCoil::isActive(){
	return out;
}
void ProgrammCoil::setValue(bool value){
	out = value;
}
void ProgrammCoil::set(){
	setValue(true);
}
void ProgrammCoil::reset(){
	setValue(false);
}
void ProgrammCoil::toggle(){
	setValue(!isActive());
}
ProgrammCoil& ProgrammCoil::operator=(bool value){
	setValue(value);
	return *this;
}


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
void Coil::setValue(bool value){
	if(value){
		gpio->BSRR |= (1 << pin);
		return;
	}
	gpio->BRR |= (1 << pin);
}
Coil& Coil::operator=(bool value){
	setValue(value);
	return *this;
}