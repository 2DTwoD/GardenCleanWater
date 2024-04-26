#include "pid.h"

void regPID::update(){
	if(!AUTO) return;
	deviation = inverse? pv - sp: sp - pv;
	if(abs(deviation) < db) return;
	e2 = e1;
	e1 = e0;
	e0 = deviation;
	out += g0 * e0 + g1 * e1 + g2 * e2;
	out = limit(out, upOutLim, downOutLim);
}
void regPID::reset(){
	out = 0.0;
	e0 = 0.0;
	e1 = 0.0;
	e2 = 0.0;
}
void regPID::updateKoef(){
	if(t == 0.0) return;
	if(ti == 0.0){
		g0 = kp * (1.0f + td / t);
	} else {
		g0 = kp * (1.0f + t / ti + td / t);
	}
	g1 = kp * (-1.0f - 2.0f * td / t);
	g2 = kp * td / t;
}