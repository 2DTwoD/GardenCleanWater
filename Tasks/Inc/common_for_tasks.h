#ifndef COMMON_FOR_TASKS_H
#define COMMON_FOR_TASKS_H

#include "FreeRTOS.h"
#include "task.h"

#include "stdint.h"
#include "coil.h"
#include "sequence.h"

void pushSeqInQueue(Sequence *seq);
Sequence* getSeqFromQueue();
void deleteSeqFromQueue(Sequence *seq);
void resetCHBsteps();

#endif //COMMON_FOR_TASKS_H