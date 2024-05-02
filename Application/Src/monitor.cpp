#include "monitor.h"

Monitor::Monitor(float valueMin, float valueMax){
	valueLimits[0] = valueMin;
	setValueMax(valueMax);
	tresDelays[0] = new CommonDelay(200);
	tresDelays[1] = new CommonDelay(200);
	tresDelays[2] = new CommonDelay(200);
	tresDelays[3] = new CommonDelay(200);
}
Monitor::~Monitor(){
	for(int i = 0; i < 4; i++){
		delete tresDelays[i];
	}
}
void Monitor::setValueMin(float limit){
	valueLimits[0] = min(limit, valueLimits[1]);
}
void Monitor::setValueMax(float limit){
	valueLimits[1] = max(limit, valueLimits[0]);
}
void Monitor::update(){
	*tresDelays[0] = value * 100 / getRange(valueLimits) <= tresholds[LL];
	*tresDelays[1] = value * 100 / getRange(valueLimits) <= tresholds[HL];
	*tresDelays[2] = value * 100 / getRange(valueLimits) >= tresholds[LH];
	*tresDelays[3] = value * 100 / getRange(valueLimits) >= tresholds[HH];
	for(int i = 0; i < 4; i++){
		tresDelays[i]->update();
	}
}
float Monitor::get(){
	return value;
}
void Monitor::set(float value){
	this->value = limit(value, valueLimits[0], valueLimits[1]);
}
void Monitor::setTreshold(TRES_TYPE tresType, uint16_t value){
	tresholds[tresType] = value;
}
void Monitor::setTresDelay(TRES_TYPE tresType, uint16_t del){
	tresDelays[tresType]->setPeriod(del);
}
bool Monitor::isHighAlarm(){
	return tresDelays[HH]->finished();
}
bool Monitor::isHighWarn(){
	return tresDelays[LH]->finished();
}
bool Monitor::isLowWarn(){
	return tresDelays[HL]->finished();
}
bool Monitor::isLowAlarm(){
	return tresDelays[LL]->finished();
}
Monitor& Monitor::operator=(float value){
	set(value);
	return *this;
}