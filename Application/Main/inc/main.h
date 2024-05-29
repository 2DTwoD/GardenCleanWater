#ifndef MAIN_H
#define MAIN_H

#include "FreeRTOS.h"
#include "task.h"

#include "init.h"
#include "global_vars.h"
#include "all_tasks.h"

extern uint8_t updateObjectsSize;
//uint32_t idleCount;

extern "C"{
	void vApplicationIdleHook ( void ){
		//idleCount++;
	}
	void vApplicationTickHook ( void ){
	}
	void vApplicationMallocFailedHook ( void ){
		while(1);
	}
	void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName ){
		( void ) pcTaskName;
		( void ) xTask;
		while(1);
	}
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		for(int i = 0; i < updateObjectsSize; i++){
			update1msObjects[i]->update1ms();
		}
	}
}
#endif //MAIN_H
