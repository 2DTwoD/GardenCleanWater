#include "pulse.h"

//Pulse
Pulse::Pulse(uint32_t period): CommonTimer(period){
}
void Pulse::update1ms(){
	if(CommonTimer::finished()){
		CommonTimer::stop();
	}
	CommonTimer::update();
}
void Pulse::set(bool value){
	if(value){
		if(!startFlag){
			startFlag = true;
			CommonTimer::start();
		}
	} else {
		if(CommonTimer::isFree()){
			startFlag = false;
		}
	}
}
bool Pulse::get(){
	return CommonTimer::inWork();
}
void Pulse::reset(){
	startFlag = false;
	CommonTimer::stop();
}
Pulse& Pulse::operator=(bool value){
	set(value);
	return *this;
}

//ShortPulse
ShortPulse::ShortPulse(uint32_t period): Pulse(period){
}
void ShortPulse::set(bool value){
	Pulse::set(value);
	if(!value) {
		Pulse::reset();
	}
	currentValue = value;
}
bool ShortPulse::get(){
	return Pulse::get() && currentValue;
}
ShortPulse& ShortPulse::operator=(bool value){
	set(value);
	return *this;
}