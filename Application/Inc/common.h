#ifndef COMMON_H
#define COMMON_H

#include "stm32f10x.h"
#include "custom_timer.h"
template<typename T>
void setRegister(T *const reg, uint32_t mask, uint32_t value);
template<typename T>
void setBitsInRegister(T * const reg, uint32_t mask, uint32_t value);
void commonInit();
void rccInit();
void tickInit();
void adcInit();
void pwmInit();

#endif //COMMON_H
