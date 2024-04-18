#ifndef SIMPLE_INPUT_H
#define SIMPLE_INPUT_H
#include "stm32f10x.h"
#include "common.h"
#include "interfaces.h"
#include "gpio_common.h"

class SimpleInput: public GPIOcommon, public ISwitch{
	public:
		SimpleInput(GPIO_TypeDef * gpio, uint8_t pin);
	
		bool isActive() override;
};

#endif //SIMPLE_INPUT_H