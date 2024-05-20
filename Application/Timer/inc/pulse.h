#ifndef PULSE_H
#define PULSE_H
#include "stdint.h"
#include "common_timer.h"

class Pulse: public IUpdated1ms  {
	private:
		bool startFlag;
		CommonTimer *timer = nullptr;
	public:
		Pulse(uint32_t period);
		~Pulse();
		void update1ms() override;
		void set(bool value);
		bool get();
		void reset();
		Pulse& operator=(bool value);
};

#endif //PULSE_H