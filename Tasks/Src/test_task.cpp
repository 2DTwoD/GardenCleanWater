#include "all_tasks.h"

extern AnalogMonitor adcMonitor;
extern Scale<float, int16_t> scale;
extern volatile uint16_t adcValues[];
extern Ramp ramp;

void testTask(void *pvParameters){
	int16_t tmp;
	while(1){
		adcMonitor.set(adcValues[0]);
		scale.set(adcMonitor.get());
		ramp.set(scale.get());
		vTaskDelay(1);
	}
}