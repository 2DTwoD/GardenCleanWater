#ifndef PID_H
#define PID_H

#include "stdint.h"

#include "interfaces.h"
#include "common.h"

class regPID: public IUpdated{
	private:
		float pv;
		float sp;
		bool AUTO;
		uint16_t inverse;
		float kp;
		float ti;
		float td;
		float t;
		float db;
		float out;
		float upOutLim;
		float downOutLim;
		float e0;
		float e1;
		float e2;
		float g0;
		float g1;
		float g2;
		float deviation;
	public:
		void update() override;
		void reset();
		void updateKoef();
};

#endif //PID_H
