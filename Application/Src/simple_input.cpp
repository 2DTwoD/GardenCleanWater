#include "simple_input.h"

SimpleInput::SimpleInput(GPIO_TypeDef * gpio, uint8_t pin): GPIOcommon(gpio, pin){
	uint8_t shift = 4 * pin;
	if(pin < 8){
		setRegister(&gpio->CRL, 0xF << shift, 0x8 << shift);
	} else {
		shift -= 32;
		setRegister(&gpio->CRH, 0xF << shift, 0x8 << shift);
	}
	gpio->ODR |= 1 << pin;
}

bool SimpleInput::isActive(){
	return (gpio->IDR & (1 << pin)) == 0;
}