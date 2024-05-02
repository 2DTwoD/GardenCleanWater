#ifndef _MONITOR_H
#define _MONITOR_H

#include "stdint.h"
#include "interfaces.h"
#include "custom_timer.h"
#include "common.h"

enum TRES_TYPE {
	LL = 0, 
	HL, 
	LH, 
	HH	
};

class Monitor: public IUpdated{
	private:
		float value;
		float valueLimits[2]{0.0f, 100.0f};
		float tresholds[4]{5.0f, 10.0f, 90.0f, 95.0f};
		CommonDelay* tresDelays[4];
		void setValueMax(float limit);
		void setValueMin(float limit);
	public:
		Monitor(float valueMin, float valueMax);
		~Monitor();
		void update() override;
		void set(float value);
		float get();
		void setTreshold(TRES_TYPE tresType, uint16_t value);
		void setTresDelay(TRES_TYPE tresType, uint16_t del);
		bool isHighAlarm();
		bool isHighWarn();
		bool isLowWarn();
		bool isLowAlarm();
		Monitor& operator=(float value);
};

#endif //_MONITOR_H