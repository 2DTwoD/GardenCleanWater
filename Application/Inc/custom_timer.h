#ifndef CUSTOM_TIMER_H
#define CUSTOM_TIMER_H
#include "stdint.h"
#include "interfaces.h"

class Delay{
	private:
		uint16_t period;
	
		uint16_t curTime;
		
		bool fin;
	
		bool impulse;
		
		ISwitch *swtch;
		
		void updateFin();
	
	public:
		Delay(ISwitch *swtch, uint16_t period);
		
		uint16_t getPeriod();
		
		void setPeriod(uint16_t value);
		
		uint16_t getCurrentTime();
		
		void setCurrentTime(uint16_t value);
		
		void reset();
		
		bool started();
		
		bool finished();
	
		bool finishedImpulse();
		
		void update();
};

#endif //CUSTOM_TIMER_H