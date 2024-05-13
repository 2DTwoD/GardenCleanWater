#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

#include "common.h"
#include "init.h"
#include "all_tasks.h"
#include "coil.h"
#include "custom_timer.h"
#include "simple_input.h"
#include "analog_monitor.h"
#include "analog_out.h"
#include "pid.h"
#include "scale.h"
#include "moving_avg.h"
#include "two_pos.h"
#include "three_pos.h"
#include "mux.h"

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
#endif //MAIN_H
