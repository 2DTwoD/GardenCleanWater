#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

#include "all_tasks.h"
#include "common.h"
#include "coil.h"

extern "C"{
	void vApplicationIdleHook ( void ){
	}
	
	void vApplicationTickHook ( void ){
	}

	void vApplicationMallocFailedHook ( void ){
		while(1);
	}

	void vApplicationStackOverflowHook( TaskHandle_t xTask,
												char * pcTaskName ){
		( void ) pcTaskName;
		( void ) xTask;
		while(1);
	}
}

void badTimeOut(){
	int i = 0;
	for(i = 0; i < 1000000; i++);
}

#endif //MAIN_H
