#include "main.h"

int main(void)
{
	rccInit();
	tickInit();
	commonInit();
	xTaskCreate(OB1Task, "OB1Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}
