#include "analog_out.h"

AnalogOut::AnalogOut(volatile uint16_t *const rawValue, uint16_t rawRange, uint32_t fullRangeTime, bool reverse): rawValue(rawValue), rawRange(rawRange){
	setFullRangeTime(fullRangeTime);
	setReverse(reverse);
}
void AnalogOut::update(){
	if(!step){
		out = sp;
		updateRawValue();
		return;
	}
	if(out < sp){
		out += step;
		if (out > sp) out = sp;
	} else if(out > sp){
		out -= step;
		if (out < sp) out = sp;
	}
	updateRawValue();
}
void AnalogOut::updateRawValue(){
	*rawValue = (uint16_t)(out * rawRange / 100.0);
	if(reverse){
		*rawValue = rawRange - *rawValue;
	}
}
float AnalogOut::getOut(){
	return out;
}
void AnalogOut::setSP(float value){
	if(value < 0.0){
		value = 0.0;
	} else if(value > 100.0){
		value = 100.0;
	}
	this->sp = value;
}
bool AnalogOut::isReverse(){
	return reverse;
}
void AnalogOut::setReverse(bool value){
	reverse = value;
}
uint32_t AnalogOut::getFullRangeTime(){
	return fullRangeTime;
}
void AnalogOut::setFullRangeTime(uint32_t value){
	if(fullRangeTime > 0){
		step = 100.0 / fullRangeTime;
	} else {
		step = 0;
	}
	this->fullRangeTime = value;
}
AnalogOut& AnalogOut::operator=(float value){
	setSP(value);
	return *this;
}