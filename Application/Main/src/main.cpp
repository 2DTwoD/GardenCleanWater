#include "main.h"

int main(void)
{
	TaskKit ob1Kit{
		&OB1step,
		&OB1s0,
		&OB1s1,
		&OB1s2,
		&OB1s3,
		&OB1s4,
		&OB1s4MeTimer,
		&OB1s5,
		&B1,
		&H1,
		&C1,
		&O1,
		&D1,
		&M1,
		&Me1,
	};
	TaskKit ob2Kit = {
		&OB2step,
		&OB2s0,
		&OB2s1,
		&OB2s2,
		&OB2s3,
		&OB2s4,
		&OB2s4MeTimer,
		&OB2s5,
		&B2,
		&H2,
		&C2,
		&O2,
		&D2,
		&M2,
		&Me2
	};
	TaskKit ob3Kit = {
		&OB3step,
		&OB3s0,
		&OB3s1,
		&OB3s2,
		&OB3s3,
		&OB3s4,
		&OB3s4MeTimer,
		&OB3s5,
		&B3,
		&H3,
		&C3,
		&O3,
		&D3,
		&M3,
		&Me3
	};
	rccInit();
	tickInit();
	commonInit();
	xTaskCreate(OB1Task, "OB1Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(OB2Task, "OB2Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(OB3Task, "OB3Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(CHBTask, "CHBTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	vTaskStartScheduler();
	while(1);
}
