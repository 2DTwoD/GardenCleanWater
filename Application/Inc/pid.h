#ifndef PID_H
#define PID_H

#include "stdint.h"

#include "interfaces.h"
#include "common.h"

class PIDreg: public IUpdated{
	private:
		float *pv;
		float t = 1.0f;
	
		float sp = 0.0f;
		float kp = 1.0f;
		float ti = 10.0f;
		float td = 0.0f;
		float db = 0.0f;
		float upOutLim = 100.0f;
		float downOutLim = 0.0f;
		bool AUTO = false;
		bool inverse = false;
	
		float out  = 0.0f;
		float e0;
		float e1;
		float e2;
		float g0;
		float g1;
		float g2;
	public:
		PIDreg(float *const pv, uint16_t t, float kp = 1.0f, float ti = 10.0f, float td = 0.0f,	float db = 0.0f, 
																			float upOutLim = 100.0f, float downOutLim = 0.0f, bool inverse = false);
		uint16_t getT();
		void setSp(float);
		float getSp();
		void setKp(float);
		float getKp();
		void setTi(float);
		float getTi();
		void setTd(float);
		float getTd();
		void setDb(float);
		float getDb();
		void setUpOutLim(float);
		float getUpOutLim();
		void setDownOutLim(float);
		float getDownOutLim();
		void setOut(float);
		float getOut();
		void setAuto(bool);
		bool isAUTO();
		void setInverse(bool);
		bool isInverse();
		void update() override;
		void reset();
		void updateKoef();
};

#endif //PID_H
