#ifndef COIL_H
#define COIL_H
#include "stm32f10x.h"

class Coil {
	private:
		uint8_t pin;
		GPIO_TypeDef * gpio;
  public:
		Coil(GPIO_TypeDef * gpio, uint8_t pin);
	
		uint8_t isActive();
	
		void setPin();
		
		void resetPin();
	
		void setValue(uint8_t value);
		
		void togglePin();
	
		Coil& operator=(int8_t value);
};

#endif //COIL_H