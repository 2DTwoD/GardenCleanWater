#include "pulse.h"

Pulse::Pulse(uint32_t period){
	timer = new CommonTimer(period);
}

Pulse::~Pulse(){
	delete timer;
}

void Pulse::update1ms(){
	if(timer->finished()){
		timer->stop();
	}
	timer->update1ms();
}

void Pulse::set(bool value){
	if(value){
		if(!startFlag){
			startFlag = true;
			timer->start();
		}
	} else {
		if(timer->isFree()){
			startFlag = false;
		}
	}
}

bool Pulse::get(){
	return timer->inWork();
}

void Pulse::reset(){
	startFlag = false;
	timer->stop();
}

Pulse& Pulse::operator=(bool value){
	set(value);
	return *this;
}