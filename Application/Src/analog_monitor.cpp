#include "analog_monitor.h"


AnalogMonitor::AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue): rawValue(rawValue){
	for(int i = 0; i < adcCapacity; i++){
		rawLimits[1] |= 1 << i;
	}
}
AnalogMonitor::AnalogMonitor(uint8_t adcCapacity, volatile uint16_t *const rawValue, float valueMin, float valueMax): AnalogMonitor(adcCapacity, rawValue){
	valueLimits[0] = valueMin;
	valueLimits[1] = valueMax;
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
}
float AnalogMonitor::getValue(){
	update();
	return value;
}
void AnalogMonitor::setValueLimits(const float *const limits){
	copyArrays(limits, valueLimits, 2);
}
void AnalogMonitor::setTresholds(const float *const tresholds){
	copyArrays(tresholds, this->tresholds, 4);
}
bool AnalogMonitor::isHighAlarm(){
	return getValue() * 100 / getRange(valueLimits) >= tresholds[3];
}
bool AnalogMonitor::isHighWarn(){
	return getValue() * 100 / getRange(valueLimits) >= tresholds[2];
}
bool AnalogMonitor::isLowWarn(){
	return getValue() * 100 / getRange(valueLimits) <= tresholds[1];
}
bool AnalogMonitor::isLowAlarm(){
	return getValue() * 100 / getRange(valueLimits) <= tresholds[0];
}