#include "all_tasks.h"

extern Coil led;
extern DIDelay ledDelay;
extern DIDelay buttonDelay;
extern ProgrammCoil ledSwitch;
extern AnalogMonitor adcMonitor;

void ledTask(void *pvParameters){
	while(1){
		adcMonitor.update();
		if(adcMonitor.isHighAlarm()){
			__NOP();
		}
		if(adcMonitor.isHighWarn()){
			__NOP();
		}
		if(adcMonitor.isLowWarn()){
			__NOP();
		}
		if(adcMonitor.isLowAlarm()){
			__NOP();
		}
		taskENTER_CRITICAL();
		if(ledDelay.finishedImpulse()){
			led = !led.isActive();
			ledDelay.reset();
		}
		taskEXIT_CRITICAL();
		if(buttonDelay.finishedImpulse()){
			led.toggle();
		}
		vTaskDelay(1);
	}
}