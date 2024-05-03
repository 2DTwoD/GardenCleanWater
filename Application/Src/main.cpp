#include "main.h"

Coil led(GPIOC, 13);
SimpleInput button(GPIOA, 0);

ProgrammCoil ledSwitch;

DIDelay ledDelay(&ledSwitch, 500);
DIDelay buttonDelay(&button, 10);
CommonDelay delay(10);

volatile uint16_t adcValues[2] = {0, 0};
AnalogMonitor adcMonitor(12, 0, 100);
AnalogOut analogOut(1000, 15000, 100, 0, 0, 100);
float pidPv = 0.0;
PIDreg pid(&pidPv, 20);
Scale<float, int16_t> scale(0.0f, 100.0f, (int16_t)0, (int16_t)100);
Ramp ramp(15000);
MovAvg avg(50);


IUpdatedInCycle *updateObjects[] = {
	&ledDelay,
	&buttonDelay,
	&delay,
	&adcMonitor,
	&analogOut,
	&ramp
};

uint8_t allTimersSize = sizeof(updateObjects) / sizeof(*updateObjects);


int main(void)
{
	adcMonitor.setTresDelay(LL, 5000);
	rccInit();
	tickInit();
	commonInit();
	adcInit();
	pwmInit();
	ledSwitch = true;
	xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(pidTask, "pidTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(testTask, "testTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}

extern "C"{
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		for(int i = 0; i < allTimersSize; i++){
			updateObjects[i]->updateInCycle();
		}
	}
	
	/*void ADC1_2_IRQHandler(void){
		if(ADC1->SR & ADC_SR_EOC){
			uint16_t val = ADC1->DR;
		}
	}*/
}
