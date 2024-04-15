#include "all_tasks.h"

extern Coil led;
extern Delay ledDelay;
extern Delay buttonDelay;
extern ProgrammSwitch ledSwitch;

void ledTask(void *pvParameters){
	while(1){
		if(buttonDelay.finishedImpulse()){
			led.togglePin();
		}
		vTaskDelay(1);
	}
}