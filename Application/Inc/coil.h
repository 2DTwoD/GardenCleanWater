#ifndef COIL_H
#define COIL_H
#include "stm32f10x.h"
#include "interfaces.h"
#include "gpio_common.h"

class Coil: public GPIOcommon, public ISwitch {
  public:
		Coil(GPIO_TypeDef * gpio, uint8_t pin);
	
		bool isActive();
	
		void setPin();
		
		void resetPin();
	
		void setValue(bool value);
		
		void togglePin();
	
		Coil& operator=(bool value);
};

#endif //COIL_H