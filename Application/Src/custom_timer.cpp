#include "custom_timer.h"

Timer::Timer(uint16_t period){
	this->period = period;
}

uint16_t Timer::getPeriod(){
	return period;
}

void Timer::setPeriod(uint16_t value){}

uint16_t Timer::getCurrentTime(){
	return curTime;
}

void Timer::setCurrentTime(uint16_t value){}

void Timer::start(){}

void Timer::stop(){}

void Timer::reset(){}

uint8_t Timer::started(){
	return go;
}

void Timer::update(){}