#ifndef SIMPLE_INPUT_H
#define SIMPLE_INPUT_H
#include "stm32f10x.h"
#include "common.h"

class SimpleInput{
	private:
		uint8_t pin;
		GPIO_TypeDef * gpio;
		uint8_t shift;
  public:
		SimpleInput(GPIO_TypeDef * gpio, uint8_t pin);
	
		uint8_t isActive();
	
		uint8_t isActiveDelayed();
};

#endif //SIMPLE_INPUT_H