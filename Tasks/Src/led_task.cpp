#include "all_tasks.h"

extern Coil led;
extern DIDelay ledDelay;
extern DIDelay buttonDelay;
extern ProgrammCoil ledSwitch;
//extern AnalogMonitor adcMonitor;
extern AnalogOut analogOut;
extern Scale<float, uint16_t> scale;
extern volatile uint16_t adcValues[];
extern ThreePosReg threePosReg;

void ledTask(void *pvParameters){
	while(1){
		//taskENTER_CRITICAL();
		/*if(ledDelay.finishedImpulse()){
			led = !led.isActive();
			ledDelay.reset();
		}*/
		bool res = threePosReg.getOut2();
		led = !res;
		//taskEXIT_CRITICAL();
		if(buttonDelay.finishedImpulse()){
			led.toggle();
		}
		vTaskDelay(1);
	}
}