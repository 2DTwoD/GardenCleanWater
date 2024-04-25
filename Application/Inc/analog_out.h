#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H

#include <stdint.h>

#include "interfaces.h"
#include "common.h"

class AnalogOut: public IUpdated{
	private:
		float out;
		float sp;
		float step;
		volatile uint16_t * const rawValue;
		uint16_t rawRange;
		bool reverse;
		uint32_t fullRangeTime;
		void updateRawValue();
	public:
		AnalogOut(volatile uint16_t *const rawValue, uint16_t rawRange, uint32_t fullRangeTime = 0, bool reverse = false);
		void update() override;
		float getOut();
		void setSP(float value);
		bool isReverse();
		void setReverse(bool value);
		uint32_t getFullRangeTime();
		void setFullRangeTime(uint32_t value);
		AnalogOut& operator=(float value);
};

#endif //ANALOG_OUT_H