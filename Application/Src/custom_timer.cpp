#include "custom_timer.h"

Delay::Delay(ISwitch *swtch, uint16_t period){
	this->swtch = swtch;
	this->period = period;
}

void Delay::updateFin(){
	fin = curTime >= period;
}

uint16_t Delay::getPeriod(){
	return period;
}

void Delay::setPeriod(uint16_t value){
	period = value;
	updateFin();
}

uint16_t Delay::getCurrentTime(){
	return curTime;
}

void Delay::setCurrentTime(uint16_t value){
	curTime = value;
	updateFin();
}

void Delay::reset(){
	curTime = 0;
	updateFin();
}

bool Delay::started(){
	return curTime > 0;
}

bool Delay::finished(){
	return fin;
}

bool Delay::finishedImpulse(){
	bool result = fin && !impulse;
	if (fin) impulse = true;
	return result;
}

void Delay::update(){
	if(swtch->isActive()){
		updateFin();
		if(fin) return;
		curTime++;
		return;
	}
	impulse = false;
	fin = false;
	curTime = 0;
}