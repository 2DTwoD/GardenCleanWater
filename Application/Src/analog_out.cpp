#include "analog_out.h"

AnalogOut::AnalogOut(uint16_t rawRange, uint32_t fullRangeTime, bool reverse, float outMin, float outMax, float limitMin, float limitMax)
	: Ramp(fullRangeTime, outMin, outMax, limitMin, limitMax), reverse(reverse){
		scale = new Scale(outMin, outMax, (uint16_t)0, rawRange);
}
void AnalogOut::update(){
	Ramp::update();
	if(reverse){
		//rawValue = (uint16_t)((getReverseOut() - getOutMin()) * rawRange / getOutRange());
	} else {
		rawValue = (uint16_t)((get() - getOutMin()) * rawRange / getOutRange());
	}
}
AnalogOut::~AnalogOut(){
	delete scale;
}
void AnalogOut::set(uint16_t value){
	Ramp::set(value);
}
bool AnalogOut::isReverse(){
	return reverse;
}
void AnalogOut::setReverse(bool value){
	reverse = value;
}
AnalogOut& AnalogOut::operator=(float value){
	set(value);
	return *this;
}