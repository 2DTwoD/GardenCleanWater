#include "on_delay.h"

OnDelay::OnDelay(uint32_t period){
	timer = new CommonTimer(period);
}

OnDelay::~OnDelay(){
	delete timer;
}

void OnDelay::update1ms(){
	timer->update1ms();
}

void OnDelay::set(bool value){
	timer->setStart(value);
}

bool OnDelay::get(){
	return timer->finished();
}

void OnDelay::reset(){
	timer->reset();
}

OnDelay& OnDelay::operator=(bool value){
	set(value);
	return *this;
}