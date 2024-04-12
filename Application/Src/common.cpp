#include "common.h"

void setRegister(volatile uint32_t * const reg, uint32_t mask, uint32_t value){
	*reg &= ~mask;
	*reg |= value;
}

void setRegister(volatile uint16_t * const reg, uint16_t mask, uint16_t value){
	*reg &= ~mask;
	*reg |= value;
}

void commonInit(){
	NVIC_SetPriorityGrouping(4);
	SystemCoreClockUpdate();
}

void rccInit(){
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));

	setRegister(&RCC->CFGR,
				RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC,
				RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC_HSE);

	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	FLASH->ACR |= FLASH_ACR_LATENCY_2;

	setRegister(&RCC->CFGR,
				RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
				RCC_CFGR_PPRE1_2);
	RCC->CFGR |= RCC_CFGR_SW_1;
	while(!(RCC->CFGR & RCC_CFGR_SWS_1));

	RCC->CFGR &= ~RCC_CR_HSION;
}

void tickInit(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 12);
	
	TIM2->PSC = 3600;
	TIM2->ARR = 2000;
	//TIM2->CR1 |= TIM_CR1_URS;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
	/*TIM2->EGR |= TIM_EGR_UG;*/
	
}

void TIM2_IRQHandler(){
	int i = 1;
	TIM2->SR &= ~TIM_SR_UIF;
}