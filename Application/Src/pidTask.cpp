#include "all_tasks.h"
extern float pidPv;
extern PIDreg pid;
extern AnalogOut analogOut;

void pidTask(void *pvParameters){
	pid.setSp(50.0f);
	pid.setKp(0.1f);
	pid.setTi(200.0f);
	pid.setTd(1.0f);
	pid.setAuto(true);
	while(1){
		pidPv = analogOut.get();
		pid.update();
		vTaskDelay(pid.getT());
	}
}