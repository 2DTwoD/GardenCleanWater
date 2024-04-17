#include "common.h"
extern volatile uint16_t adcValues[];

void setRegister(volatile uint32_t * const reg, uint32_t mask, uint32_t value){
	*reg &= ~mask;
	*reg |= value;
}

void setRegister(volatile uint16_t * const reg, uint16_t mask, uint16_t value){
	*reg &= ~mask;
	*reg |= value;
}

int8_t getPosition(uint32_t mask){
	int i = 0;
	while(i < 32){
		if(mask & (1<<i)) return i;
		i++;
	}
	return -1;
}

void setBitsInRegister(volatile uint32_t * const reg, uint32_t mask, uint32_t value){
	int8_t pos = getPosition(mask);
	if(pos < 0) return;
	*reg &= ~mask;
	*reg |= (value << pos);
}

void badTimeOut(uint32_t value){
	for(int i = 0; i < value; i++);
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
	
	//ADC prescale
	setRegister(&RCC->CFGR, RCC_CFGR_ADCPRE, RCC_CFGR_ADCPRE_DIV6);

	RCC->CFGR &= ~RCC_CR_HSION;
}

void tickInit(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 36;
	TIM2->ARR = 2000;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 6);
}

void adcInit(){
	//APB2 peripheral clock enable
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	//Enable DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	//GPIO set for ADC
	setBitsInRegister(&GPIOA->CRL, GPIO_CRL_MODE5 | GPIO_CRL_CNF5, 0b0000);
	setBitsInRegister(&GPIOA->CRL, GPIO_CRL_MODE6 | GPIO_CRL_CNF6, 0b0000);
	
	//Enable interrupt
	/*ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);*/
	
	//ADC sample time 239.5 cycles
	setBitsInRegister(&ADC1->SMPR2, ADC_SMPR2_SMP5, 0b111);
	setBitsInRegister(&ADC1->SMPR2, ADC_SMPR2_SMP6, 0b111);
	//ADC regular sequence (channel #5 first, then #6)
	setBitsInRegister(&ADC1->SQR3, ADC_SQR3_SQ1, 6);
	setBitsInRegister(&ADC1->SQR3, ADC_SQR3_SQ2, 5);
	//num of channels to scan
	setBitsInRegister(&ADC1->SQR1, ADC_SQR1_L, 0b1);
	//DMA enable and scan
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_DMA;
	//A/D converter ON, Continuous conversion
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	//A/D converter ON again
	ADC1->CR2 |= ADC_CR2_ADON;
	//ADC calibration
	badTimeOut(100000);
	ADC1->CR2 |= ADC_CR2_CAL;
	
	//periphery address
	DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);
	//memory address
	DMA1_Channel1->CMAR = (uint32_t)adcValues;
	//number of replacing in memory
	DMA1_Channel1->CNDTR = 2;
	//dma set circular and increment
	DMA1_Channel1->CCR |=	DMA_CCR1_CIRC | DMA_CCR1_MINC;
	setBitsInRegister(&DMA1_Channel1->CCR, DMA_CCR1_MSIZE, 0b01);
	setBitsInRegister(&DMA1_Channel1->CCR, DMA_CCR1_PSIZE, 0b01);
	//dma enable;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
	
}

