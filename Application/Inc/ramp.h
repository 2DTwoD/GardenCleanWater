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
	protected:
		float getOutMin();
	public:
		Ramp(uint32_t fullRangeTime = 0);
		Ramp(uint32_t fullRangeTime, float outMin, float outMax);
		Ramp(uint32_t fullRangeTime, float outMin, float outMax, float limitMin, float limitMax);
		void update() override;
		float getOut();
		float getReverseOut();
		void setSP(float value);
		uint32_t getFullRangeTime();
		void setFullRangeTime(uint32_t value);
		void setOutMin(float value);
		void setOutMax(float value);
		void setLimMin(float value);
		void setLimMax(float value);
		float getOutRange();
		Ramp& operator=(float value);
};

#endif //RAMP_H