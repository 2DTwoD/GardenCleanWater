#include "coil.h"

//ProgrammCoil
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

//Coil
Coil::Coil(GPIO_TypeDef *gpio, uint8_t pin): GPIOcommon(gpio, pin) {
	if(pin < 8){
		setBitsInRegister(&gpio->CRL, 0x1111 << (4 * pin), 0b0001);
	} else {
		setBitsInRegister(&gpio->CRH, 0x1111 << (4 * pin - 32), 0b0001);
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

//CoilDelayed
CoilDelayed::CoilDelayed(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay): Coil(gpio, pin), CommonTimer(delay) {
}
void CoilDelayed::update1ms() {
	CommonTimer::update1ms();
	Coil::setValue(CommonTimer::finished());
}
bool CoilDelayed::isActive(){
	return Coil::isActive();
}
void CoilDelayed::setValue(bool value){
	CommonTimer::setStart(value);
}
CoilDelayed& CoilDelayed::operator=(bool value){
	setValue(value);
	return *this;
}

//CoilPulse
CoilPulse::CoilPulse(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay): Coil(gpio, pin), CommonTimer(delay) {
}
void CoilPulse::update1ms() {
	CommonTimer::update1ms();
	Coil::setValue(CommonTimer::inWork());
}
bool CoilPulse::isActive(){
	return Coil::isActive();
}
void CoilPulse::setValue(bool value){
	CommonTimer::setStart(value);
}
CoilPulse& CoilPulse::operator=(bool value){
	setValue(value);
	return *this;
}