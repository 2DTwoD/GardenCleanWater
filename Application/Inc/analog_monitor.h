#ifndef ANALOG_MONITOR_H
#define ANALOG_MONITOR_H
#include "stdint.h"

class AnalogMonitor{
	private:
		volatile uint16_t *rawValue;
		float value;
		volatile uint16_t rawLimits[2]{0, 0};
		float valueLimits[2]{0.0, 100.0};
		float tresholds[4]{5.0, 10.0, 90.0, 95.0};
		template<typename T>
		T getRange(const T *const limits);
		template<typename T>
		void copyArrays(const T *const src, T *const dst, uint8_t len);
	public:
		AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue);
		AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue, float valueMin, float valueMax);
		void update();
		float getValue();
		void setValueLimits(const float *const limits);
		void setTresholds(const float *const tresholds);
		bool isHighAlarm();
		bool isHighWarn();
		bool isLowWarn();
		bool isLowAlarm();
};

#endif //ANALOG_MONITOR_H