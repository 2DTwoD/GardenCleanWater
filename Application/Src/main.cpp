#include "main.h"

Coil led(GPIOC, 13);
SimpleInput button(GPIOA, 0);

ProgrammCoil ledSwitch;

DIDelay ledDelay(&ledSwitch, 500);
DIDelay buttonDelay(&button, 10);
CommonDelay delay(10);

volatile uint16_t adcValues[2] = {0, 0};
AnalogMonitor adcMonitor(12, adcValues);


IUpdated *updateObjects[] = {
	&ledDelay,
	&buttonDelay,
	&delay,
	&adcMonitor
};

uint8_t allTimersSize = sizeof(updateObjects) / sizeof(*updateObjects);


int main(void)
{
	adcMonitor.setTresDelays(LL, 5000);
	rccInit();
	tickInit();
	commonInit();
	adcInit();
	pwmInit();
	ledSwitch = true;
	xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}

extern "C"{
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		for(int i = 0; i < allTimersSize; i++){
			updateObjects[i]->update();
		}
	}
	
	/*void ADC1_2_IRQHandler(void){
		if(ADC1->SR & ADC_SR_EOC){
			uint16_t val = ADC1->DR;
		}
	}*/
}
