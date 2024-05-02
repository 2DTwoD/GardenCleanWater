#ifndef RAMP_H
#define RAMP_H

#include <stdint.h>

#include "interfaces.h"
#include "common.h"

class Ramp: public IUpdated{
	private:
		float out;
		float reverseOut;
		float sp;
		float step;
		uint32_t fullRangeTime;
		float outRange[2];
		float outLimits[2];
		void setOutMin(float value);
		void setOutMax(float value);
	protected:
		float getOutMin();
		float getOutRange();
	public:
		Ramp(uint32_t fullRangeTime = 0);
		Ramp(uint32_t fullRangeTime, float outMin, float outMax);
		Ramp(uint32_t fullRangeTime, float outMin, float outMax, float limitMin, float limitMax);
		void update() override;
		float get();
		void set(float value);
		uint32_t getFullRangeTime();
		void setFullRangeTime(uint32_t value);
		void setLimMin(float value);
		void setLimMax(float value);
		Ramp& operator=(float value);
};

#endif //RAMP_H