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
	valueLimits[1] = valueMax;
}
AnalogMonitor::~AnalogMonitor(){
	for(int i = 0; i < 4; i++){
		delete tresDelays[i];
	}
}
template<typename T>
T AnalogMonitor::getRange(const T *const limits){
	return limits[1] - limits[0];
}
template<typename T>
void AnalogMonitor::copyArrays(const T *const src, T *const dst, uint8_t len){
	for(int i = 0; i < len; i++){
		dst[i] = src[i];
	}
}
void AnalogMonitor::update(){
	value = valueLimits[0] + getRange(valueLimits) / getRange(rawLimits) * (*rawValue + rawLimits[0]);
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
void AnalogMonitor::setValueLimits(const float *const limits){
	copyArrays(limits, valueLimits, 2);
}
void AnalogMonitor::setTresholds(const float *const tresholds){
	copyArrays(tresholds, this->tresholds, 4);
}
void AnalogMonitor::setTresDelays(TRES_TYPE tresType, uint16_t del){
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