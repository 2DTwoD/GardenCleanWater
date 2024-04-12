#include "main.h"

Coil led(GPIOC, 13);

int main()
{
	rccInit();
	//tickInit();
	commonInit();
	xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
	while(1);
}
