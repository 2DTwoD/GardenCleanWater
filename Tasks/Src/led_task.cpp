#include "all_tasks.h"

extern Coil led;
extern DIDelay ledDelay;
extern DIDelay buttonDelay;
extern ProgrammSwitch ledSwitch;

void ledTask(void *pvParameters){
	while(1){
		if(ledDelay.finishedImpulse()){
			taskENTER_CRITICAL();
			led.togglePin();
			taskEXIT_CRITICAL();
			ledDelay.reset();
		}
		vTaskDelay(1);
	}
}