#ifndef ALL_TASKS_H
#define ALL_TASKS_H
#include "stdint.h"

#include "FreeRTOS.h"
#include "task.h"

#include "common_for_tasks.h"
#include "coil.h"
#include "coil_with_timer.h"
#include "simple_input.h"
#include "sequence.h"
#include "common_timer.h"
#include "on_delay.h"
#include "pulse.h"

void OBTask(void *pvParameters);
void OB1Task(void *pvParameters);
void OB2Task(void *pvParameters);
void OB3Task(void *pvParameters);
void CHBTask(void *pvParameters);

#endif //ALL_TASKS_H