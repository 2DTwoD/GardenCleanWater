#ifndef COMMON_FOR_TASKS_H
#define COMMON_FOR_TASKS_H

#include "stdint.h"
#include "sequence.h"

void pushSeqInQueue(Sequence *seq);
Sequence* getSeqFromQueue();
void deleteSeqFromQueue(Sequence *seq);

#endif //COMMON_FOR_TASKS_H