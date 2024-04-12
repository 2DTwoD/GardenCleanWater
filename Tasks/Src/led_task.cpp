#include "all_tasks.h"

extern Coil led;

void ledTask(void *pvParameters){
	while(1){
		led.togglePin();
		vTaskDelay(1000);
	}
}