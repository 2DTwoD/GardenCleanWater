#include "all_tasks.h"

extern AnalogMonitor adcMonitor;
extern Scale<float, int16_t> scale;
extern volatile uint16_t adcValues[];
extern Ramp ramp;
extern AnalogOut analogOut;
extern MovAvg avg;
extern TwoPosTim twoPos;
extern ThreePosReg threePosReg;

void testTask(void *pvParameters){
	int16_t tmp;
	while(1){
		adcMonitor = adcValues[0];
		
		avg = adcMonitor.get();
		
		scale = avg.get();
		
		ramp = scale.get();
		
		analogOut = avg.get();
		
		twoPos = avg.get();
		
		//threePosReg = avg.get();
		vTaskDelay(1);
	}
}