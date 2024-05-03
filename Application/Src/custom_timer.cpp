#include "custom_timer.h"

//CommonDelay implementation
CommonDelay::CommonDelay(uint16_t period){
	this->period = period;
}
void CommonDelay::updateInCycle(){
	if(started()){
		fin = curTime >= period;
		if(fin) return;
		curTime++;
		return;
	}
	impulse = false;
	fin = false;
	curTime = 0;
}
uint16_t CommonDelay::getPeriod(){
	return period;
}
void CommonDelay::setPeriod(uint16_t value){
	period = value;
}
uint16_t CommonDelay::getCurrentTime(){
	return curTime;
}
void CommonDelay::setCurrentTime(uint16_t value){
	curTime = value;
}
void CommonDelay::start(){
	go = true;
}
void CommonDelay::pause(){
	if(finished()) return;
	go = false;
}
void CommonDelay::stop(){
	go = false;
	reset();
}
void CommonDelay::reset(){
	curTime = 0;
	impulse = false;
}
void CommonDelay::prepareAndStart(){
	stop();
	start();
}
void CommonDelay::setStart(bool value){
	if(value){
		start();
	} else {
		stop();
	}
}
CommonDelay& CommonDelay::operator=(bool value){
	setStart(value);
	return *this;
}
bool CommonDelay::started(){
	return go;
}
bool CommonDelay::notFinished(){
 return curTime < period;
}
bool CommonDelay::finished(){
 return curTime >= period;
}
bool CommonDelay::finishedImpulse(){
	bool result = finished() && !impulse;
	if (finished()) impulse = true;
	return result;
}

//DIDelay implementation
DIDelay::DIDelay(ISwitch *swtch, uint16_t period): CommonDelay(period){
	this->swtch = swtch;
}
bool DIDelay::started(){
	return CommonDelay::started() || swtch->isActive();
}