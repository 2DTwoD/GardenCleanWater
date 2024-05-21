#ifndef COIL_H
#define COIL_H

#include "stm32f10x.h"
#include "interfaces.h"
#include "gpio_common.h"
#include "common.h"
#include "common_timer.h"

class ProgrammCoil: public ISwitch{
	private:
		bool out;
	public:
		virtual bool isActive() override;
		virtual void setValue(bool value);
		void set();
		void reset();
		void toggle();
		ProgrammCoil& operator=(bool value);
};

class Coil: public GPIOcommon, public ProgrammCoil {
  public:
		Coil(GPIO_TypeDef *gpio, uint8_t pin);
	
		bool isActive() override;
	
		void setValue(bool value) override;
	
		Coil& operator=(bool value);
};

class CoilDelayed: private CommonTimer, public Coil, public IUpdated1ms {
  public:
		CoilDelayed(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay);
	
		void update1ms() override;
			
		bool isActive() override;
	
		void setValue(bool value) override;
	
		CoilDelayed& operator=(bool value);
};

class CoilPulse: private CommonTimer, public Coil, public IUpdated1ms {
  public:
		CoilPulse(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay);
	
		void update1ms() override;
			
		bool isActive() override;
	
		void setValue(bool value) override;
	
		CoilPulse& operator=(bool value);
};
#endif //COIL_H