#ifndef _MOVING_AVG
#define _MOVING_AVG
#include <cstring>
#include "stdint.h"
#include "stdlib.h"

#include "common.h"
#include "interfaces.h"

class MovAvg: public IUpdatedSomewhere{
	private:
		float *row = nullptr;
		//float row[100];
		uint8_t size;
		uint8_t pos;
		float in;
		float out;
	public:
		MovAvg(uint8_t size = 1);
		~MovAvg();
		void set(float value);
		float get();
		void updateSomewhere() override;
		float *const getInRef();
		float *const getOutRef();
};

#endif //_MOVING_AVG
