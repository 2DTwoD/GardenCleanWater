#include "off_delay.h"

OffDelay::OffDelay(uint32_t period){
	timer = new CommonTimer(period);
}

OffDelay::~OffDelay(){
	delete timer;
}

void OffDelay::update1ms(){
	if(timer->finished()){
		timer->stop();
	}
	timer->update1ms();
}

void OffDelay::set(bool value){
	if(!value){
		if(startFlag){
			timer->prepareAndStart();
		}
	} else {
		timer->stop();
	}
	startFlag = value;
}

bool OffDelay::get(){
	return startFlag || timer->inWork();
}

void OffDelay::reset(){
	timer->finish();
}

OffDelay& OffDelay::operator=(bool value){
	set(value);
	return *this;
}