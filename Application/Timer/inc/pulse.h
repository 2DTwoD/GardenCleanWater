#ifndef PULSE_H
#define PULSE_H
#include "stdint.h"
#include "common_timer.h"

class Pulse:private CommonTimer, public IUpdated1ms  {
	private:
		bool startFlag;
	public:
		Pulse(uint32_t period);
		void update1ms() override;
		void set(bool value);
		bool get();
		void reset();
		Pulse& operator=(bool value);
};

class ShortPulse: public Pulse  {
	private:
		bool currentValue;
	public:
		ShortPulse(uint32_t period);
		void set(bool value);
		bool get();
		ShortPulse& operator=(bool value);
};

#endif //PULSE_H