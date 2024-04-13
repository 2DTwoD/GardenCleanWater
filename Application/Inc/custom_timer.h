#ifndef CUSTOM_TIMER_H
#define CUSTOM_TIMER_H
#include "stdint.h"

class Timer{
	private:
		uint16_t period;
	
		uint16_t curTime;
	
		uint8_t go;
	
	public:
		Timer(uint16_t period);
		
		uint16_t getPeriod();
		
		void setPeriod(uint16_t value);
		
		uint16_t getCurrentTime();
		
		void setCurrentTime(uint16_t value);
		
		void start();
		
		void stop();
		
		void reset();
		
		uint8_t started();
		
		void update();
};

#endif //CUSTOM_TIMER_H