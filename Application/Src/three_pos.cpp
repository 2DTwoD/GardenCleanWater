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
	if(reverse){
		return out2;
	}
	return out1;
}
bool ThreePosReg::getOut2(){
	if(reverse){
		return out1;
	}
	return out2;
}
void ThreePosReg::update1ms(){
	float sub = in - sp;
	if(sub < -pulseGist){
		out1 = pauseTimer->isFree() && !out2;
		out2 = pauseTimer->isFree() && !out1;
	} else if(sub < -zeroGist){
		out1 = pulseTimer->inWork() && !out2;
		out2 = pulseTimer->inWork() && !out1;
		startTimer = true;
	} else if(sub < 0.0f){
		out1 = pulseTimer->inWork() && !out2;
		out2 = pulseTimer->inWork() && !out1;
	} else if(sub < zeroGist){
		out2 = pulseTimer->inWork() && !out1;
		out1 = pulseTimer->inWork() && !out2;
	}  else if(sub < pulseGist){
		out2 = pulseTimer->inWork() && !out1;
		out1 = pulseTimer->inWork() && !out2;
		startTimer = true;
	} else {
		out2 = pauseTimer->isFree() && !out1;
		out1 = pauseTimer->isFree() && !out2;
	}
	pauseTimer->update1ms();
	pulseTimer->update1ms();
	if(startTimer){
		*pauseTimer = pulseTimer->notFinished();
		if(pulseTimer->finished()){
			startTimer = false;
		}
	}
	*pulseTimer = pauseTimer->finished();
}
float *const ThreePosReg::getInRef(){
	return &in;
}
bool *const ThreePosReg::getOut1Ref(){
	if(reverse){
		return &out2;
	}
	return &out1;
}
bool *const ThreePosReg::getOut2Ref(){
	if(reverse){
		return &out1;
	}
	return &out2;
}