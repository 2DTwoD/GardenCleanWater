#include "off_delay.h"

OffDelay::OffDelay(uint32_t period): CommonTimer(period){
}
void OffDelay::update1ms(){
	if(CommonTimer::finished()){
		CommonTimer::stop();
	}
	CommonTimer::update();
}
void OffDelay::set(bool value){
	if(!value){
		if(startFlag){
			CommonTimer::prepareAndStart();
		}
	} else {
		CommonTimer::stop();
	}
	startFlag = value;
}
bool OffDelay::get(){
	return startFlag || CommonTimer::inWork();
}
void OffDelay::reset(){
	CommonTimer::finish();
}
OffDelay& OffDelay::operator=(bool value){
	set(value);
	return *this;
}