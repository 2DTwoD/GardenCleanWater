#include "all_tasks.h"

extern Coil led;
extern DIDelay ledDelay;
extern DIDelay buttonDelay;
extern ProgrammCoil ledSwitch;

void ledTask(void *pvParameters){
	while(1){
		if(ledDelay.finishedImpulse()){
			//taskENTER_CRITICAL();
			led = !led.isActive();
			//taskEXIT_CRITICAL();
			ledDelay.reset();
		}
		if(buttonDelay.finishedImpulse()){
			led.toggle();
		}
		vTaskDelay(1);
	}
}