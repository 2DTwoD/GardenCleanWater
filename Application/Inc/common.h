#ifndef COMMON_H
#define COMMON_H

#include "stm32f10x.h"

void setRegister(volatile uint32_t *const reg, uint32_t mask, uint32_t value);
void setRegister(volatile uint16_t *const reg, uint16_t mask, uint16_t value);
void commonInit();
void rccInit();
void tickInit();
void adcInit();

#endif //COMMON_H
