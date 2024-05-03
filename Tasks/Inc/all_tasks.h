#ifndef ALL_TASKS_H
#define ALL_TASKS_H
#include "stdint.h"

#include "FreeRTOS.h"
#include "task.h"

#include "coil.h"
#include "custom_timer.h"
#include "simple_input.h"
#include "analog_monitor.h"
#include "analog_out.h"
#include "pid.h"
#include "scale.h"
#include "moving_avg.h"

void ledTask(void *pvParameters);
void pidTask(void *pvParameters);
void testTask(void *pvParameters);

#endif //ALL_TASKS_H