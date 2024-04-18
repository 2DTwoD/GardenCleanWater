#ifndef PROGRAMM_SWITCH_H
#define PROGRAMM_SWITCH_H
#include "interfaces.h"

class ProgrammSwitch: public ISwitch{
	private:
		bool status;
	
	public:
		void set();
	
		void reset();
	
		void toggle();
	
		void setValue(bool value);
	
		bool isActive() override;
		
		ProgrammSwitch& operator=(bool value);
};

#endif //PROGRAMM_SWITCH_H