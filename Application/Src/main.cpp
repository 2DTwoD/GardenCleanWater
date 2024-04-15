#include "main.h"

Coil led(GPIOC, 13);
SimpleInput button(GPIOA, 0);

ProgrammSwitch ledSwitch;

Delay ledDelay(&ledSwitch, 500);
Delay buttonDelay(&button, 10);

Delay *allTimers[] = {
	&ledDelay,
	&buttonDelay
};

uint8_t allTimersSize = sizeof(allTimers) / sizeof(*allTimers);

int main(void)
{
	rccInit();
	tickInit();
	commonInit();
	//ledSwitch = true;
	xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}

extern "C"{
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		for(int i = 0; i < allTimersSize; i++){
			allTimers[i]->update();
		}
	}
}