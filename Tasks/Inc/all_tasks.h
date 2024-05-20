#ifndef ALL_TASKS_H
#define ALL_TASKS_H
#include "stdint.h"

#include "FreeRTOS.h"
#include "task.h"

#include "common_for_tasks.h"
#include "coil.h"
#include "simple_input.h"
#include "sequence.h"
#include "common_timer.h"
#include "on_delay.h"
#include "pulse.h"

void OB1Task(void *pvParameters);
void CHBTask(void *pvParameters);

#endif //ALL_TASKS_H