#include "main.h"

Coil led(GPIOC, 13);
int counter = 0;
int main(void)
{
	rccInit();
	tickInit();
	commonInit();
	xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}

extern "C"{
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		if(counter > 1000){
			led.togglePin();
			counter = 0;
		}
		counter++;
	}
}