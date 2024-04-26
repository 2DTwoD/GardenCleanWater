#include "analog_out.h"

AnalogOut::AnalogOut(volatile uint16_t *const rawValue, uint16_t rawRange, uint32_t fullRangeTime, bool reverse, float outMin, float outMax, float limitMin, float limitMax)
	: rawValue(rawValue), rawRange(rawRange), Ramp(fullRangeTime, outMin, outMax, limitMin, limitMax), reverse(reverse){
}
void AnalogOut::update(){
	Ramp::update();
	if(reverse){
		*rawValue = (uint16_t)((getReverseOut() - getOutMin()) * rawRange / getOutRange());
	} else {
		*rawValue = (uint16_t)((getOut() - getOutMin()) * rawRange / getOutRange());
	}
}
bool AnalogOut::isReverse(){
	return reverse;
}
void AnalogOut::setReverse(bool value){
	reverse = value;
}
AnalogOut& AnalogOut::operator=(float value){
	setSP(value);
	return *this;
}