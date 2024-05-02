#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H

#include <stdint.h>

#include "interfaces.h"
#include "common.h"
#include "ramp.h"
#include "scale.h"

class AnalogOut: public Ramp{
	private:
		Scale<float, uint16_t> *scale = nullptr;
		uint16_t rawValue;
		uint16_t rawRange;
		bool reverse;
	public:
		AnalogOut(uint16_t rawRange, uint32_t fullRangeTime = 0, bool reverse = false,
							float outMin = 0.0f, float outMax = 100.0f, float limitMin = 0.0f, float limitMax = 100.0f);
		~AnalogOut();
		void set(uint16_t value);
		void update() override;
		bool isReverse();
		void setReverse(bool value);
		AnalogOut& operator=(float value);
};

#endif //ANALOG_OUT_H