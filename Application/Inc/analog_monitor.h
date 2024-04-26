#ifndef ANALOG_MONITOR_H
#define ANALOG_MONITOR_H

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

class AnalogMonitor: public IUpdated{
	private:
		volatile uint16_t *rawValue;
		float value;
		volatile uint16_t rawLimits[2]{0, 0};
		float valueLimits[2]{0.0f, 100.0f};
		float tresholds[4]{5.0f, 10.0f, 90.0f, 95.0f};
		CommonDelay* tresDelays[4];
	public:
		AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue);
		AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue, float valueMin, float valueMax);
		~AnalogMonitor();
		void update() override;
		float getValue();
		void setValueMax(float limit);
		void setValueMin(float limit);
		void setTreshold(TRES_TYPE tresType, uint16_t value);
		void setTresDelay(TRES_TYPE tresType, uint16_t del);
		bool isHighAlarm();
		bool isHighWarn();
		bool isLowWarn();
		bool isLowAlarm();
};

#endif //ANALOG_MONITOR_H