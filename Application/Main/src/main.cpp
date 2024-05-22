#include "main.h"

int main(void)
{
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
