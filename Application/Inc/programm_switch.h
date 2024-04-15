#ifndef PROGRAMM_SWITCH_H
#define PROGRAMM_SWITCH_H
#include "interfaces.h"

class ProgrammSwitch: public ISwitch{
	private:
		bool status;
	
	public:
		void set();
	
		void reset();
	
		void setValue(bool value);
	
		bool isActive();
		
		ProgrammSwitch& operator=(bool value);
};

#endif //PROGRAMM_SWITCH_H