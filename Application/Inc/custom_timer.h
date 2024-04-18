#ifndef CUSTOM_TIMER_H
#define CUSTOM_TIMER_H
#include "stdint.h"
#include "interfaces.h"

class CommonDelay {
	protected:
		uint16_t period;
		uint16_t curTime;
		bool go;
		bool fin;
		bool impulse;
	public:
		CommonDelay(uint16_t period);
		uint16_t getPeriod();
		void setPeriod(uint16_t value);
		uint16_t getCurrentTime();
		void setCurrentTime(uint16_t value);
		void start();
		void pause();
		void stop();
		void reset();
		void prepareAndStart();
		virtual bool started();
		bool notFinished();
		bool finished();
		bool finishedImpulse();
		void update();
};

class DIDelay: public CommonDelay{
	private:
		ISwitch *swtch;
	public:
		DIDelay(ISwitch *swtch, uint16_t period);
		bool started() override;
};

#endif //CUSTOM_TIMER_H