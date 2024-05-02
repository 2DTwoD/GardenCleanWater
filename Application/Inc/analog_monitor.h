#ifndef _ANALOG_MONITOR_H
#define _ANALOG_MONITOR_H

#include "stdint.h"
#include "interfaces.h"
#include "custom_timer.h"
#include "monitor.h"
#include "common.h"
#include "scale.h"

class AnalogMonitor: public Monitor{
	private:
		Scale<uint16_t, float> *analogScale = nullptr;
	public:
		AnalogMonitor(uint8_t adcCapacity, float valueMin = 0.0f, float valueMax = 0.0f);
		~AnalogMonitor();
		void set(uint16_t value);
};

#endif //_ANALOG_MONITOR_H