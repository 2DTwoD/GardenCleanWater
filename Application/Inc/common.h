#ifndef COMMON_H
#define COMMON_H
#include "stdint.h"

void badTimeOut(uint32_t);

int8_t getPosition(volatile uint32_t mask);

template<typename T>
void setRegister(T * const reg, uint32_t mask, uint32_t value){
	*reg &= ~mask;
	*reg |= value;
}

template<typename T>
void setBitsInRegister(T * const reg, uint32_t mask, uint32_t value){
	int8_t pos = getPosition(mask);
	if(pos < 0) return;
	*reg &= ~mask;
	*reg |= (value << pos);
}

template<typename T>
T max(T val1, T val2){
	if(val1 > val2){
		 return val1;
	}
	return val2;
}

template<typename T>
T min(T val1, T val2){
	if(val1 < val2){
		 return val1;
	}
	return val2;
}

template<typename T>
T limit(T value, T min, T max){
	if(value < min){
		value = min;
	} else if(value > max){
		value = max;
	}
	return value;
}

template<typename T>
T getRange(const T *const limits){
	return limits[1] - limits[0];
}

template<typename T>
void copyArrays(const T *const src, T *const dst, uint8_t len){
	for(int i = 0; i < len; i++){
		dst[i] = src[i];
	}
}
#endif //COMMON_H
