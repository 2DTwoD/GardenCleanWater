#include "analog_monitor.h"


AnalogMonitor::AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue): rawValue(rawValue){
	for(int i = 0; i < adcCapacity; i++){
		rawLimits[1] |= 1 << i;
	}
	tresDelays[0] = new CommonDelay(200);
	tresDelays[1] = new CommonDelay(200);
	tresDelays[2] = new CommonDelay(200);
	tresDelays[3] = new CommonDelay(200);
}
AnalogMonitor::AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue, float valueMin, float valueMax): AnalogMonitor(adcCapacity, rawValue){
	valueLimits[0] = valueMin;
	setValueMax(valueMax);
}
AnalogMonitor::~AnalogMonitor(){
	for(int i = 0; i < 4; i++){
		delete tresDelays[i];
	}
}
void AnalogMonitor::update(){
	value = valueLimits[0] + getRange(valueLimits) / getRange(rawLimits) * (*rawValue - rawLimits[0]);
	*tresDelays[0] = value * 100 / getRange(valueLimits) <= tresholds[0];
	*tresDelays[1] = value * 100 / getRange(valueLimits) <= tresholds[1];
	*tresDelays[2] = value * 100 / getRange(valueLimits) >= tresholds[2];
	*tresDelays[3] = value * 100 / getRange(valueLimits) >= tresholds[3];
	for(int i = 0; i < 4; i++){
		tresDelays[i]->update();
	}
}
float AnalogMonitor::getValue(){
	return value;
}
void AnalogMonitor::setValueMin(float limit){
	valueLimits[0] = min(limit, valueLimits[1]);
}
void AnalogMonitor::setValueMax(float limit){
	valueLimits[1] = max(limit, valueLimits[0]);
}
void AnalogMonitor::setTreshold(TRES_TYPE tresType, uint16_t value){
	tresholds[tresType] = value;
}
void AnalogMonitor::setTresDelay(TRES_TYPE tresType, uint16_t del){
	tresDelays[tresType]->setPeriod(del);
}
bool AnalogMonitor::isHighAlarm(){
	return tresDelays[3]->finished();
}
bool AnalogMonitor::isHighWarn(){
	return tresDelays[2]->finished();
}
bool AnalogMonitor::isLowWarn(){
	return tresDelays[1]->finished();
}
bool AnalogMonitor::isLowAlarm(){
	return tresDelays[0]->finished();
}