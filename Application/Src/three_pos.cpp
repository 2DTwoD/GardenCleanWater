#include "three_pos.h"

ThreePosReg::ThreePosReg(float sp, float zeroGist, float pulseGist, uint16_t pauseTime, uint16_t pulseTime, bool reverse): sp(sp), zeroGist(zeroGist), reverse(reverse){
		pauseTimer = new CommonDelay(pauseTime);
		pulseTimer = new CommonDelay(pulseTime);
		setPulseGist(pulseGist);
}
ThreePosReg::~ThreePosReg(){
	delete pauseTimer;
	delete pulseTimer;
}
void ThreePosReg::set(float value){
	in = value;
}
ThreePosReg& ThreePosReg::operator=(float value){
	set(value);
	return *this;
}
void ThreePosReg::setSp(float value){
	sp = value;
}
float ThreePosReg::getSp(){
	return sp;
}
void ThreePosReg::setZeroGist(float value){
	zeroGist = min(abs(value), pulseGist);
}
float ThreePosReg::getZeroGist(){
	return zeroGist;
}
void ThreePosReg::setPulseGist(float value){
	pulseGist = max(abs(value), zeroGist);
}
float ThreePosReg::getPulseGist(){
	return pulseGist;
}
void ThreePosReg::setPauseTime(uint16_t value){
	pauseTimer->setPeriod(value);
}
uint16_t ThreePosReg::getPauseTime(){
	return pauseTimer->getPeriod();
}
void ThreePosReg::setPulseTime(uint16_t value){
	pulseTimer->setPeriod(value);
}
uint16_t ThreePosReg::getPulseTime(){
	return pulseTimer->getPeriod();
}
void ThreePosReg::setReverse(bool value){
	reverse = value;
}
bool ThreePosReg::getReverse(){
	return reverse;
}
bool ThreePosReg::getOut1(){
	return out1;
}
bool ThreePosReg::getOut2(){
	return out2;
}
void ThreePosReg::update1ms(){
	uint8_t action;
	if(in < sp - pulseGist){
		action = OUT1_STOP;
	} else if(in < sp - zeroGist){
		action = OUT1_PULSE;
	} else if(in < sp + zeroGist){
		action = ALL_STOP;
	} else if(in < sp + pulseGist){
		action = OUT2_PULSE;
	} else {
		action = OUT2_STOP;
	}
	if(OUT1_PULSE){
		*pauseTimer = action == OUT1_PULSE && pulseTimer->notFinished();
		*pulseTimer = action == OUT1_PULSE && pauseTimer->finished();
	}
	pauseTimer->update1ms();
	pulseTimer->update1ms();
	out1 = action != ALL_STOP || pulseTimer->started();
	//out2 = (action != ALL_STOP || pulseTimer->inWork()) && !out1;
}
float *const ThreePosReg::getInRef(){
	return &in;
}
bool *const ThreePosReg::getOut1Ref(){
	return &out1;
}
bool *const ThreePosReg::getOut2Ref(){
	return &out2;
}