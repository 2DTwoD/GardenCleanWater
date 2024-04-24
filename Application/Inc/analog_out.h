#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H
#include "interfaces.h"

class AnalogOut: public IUpdated{
	private:
		float value;
		uint16_t * const rawValue;
		uint16_t range;
		bool reverse;
	public:
		AnalogOut(uint16_t *const rawValue, uint16_t range);
		void update() override;
};

#endif //ANALOG_OUT_H