#ifndef ALL_TASKS_H
#define ALL_TASKS_H

#include "FreeRTOS.h"
#include "task.h"

#include "coil.h"
#include "custom_timer.h"
#include "simple_input.h"

void ledTask(void *pvParameters);

#endif //ALL_TASKS_H