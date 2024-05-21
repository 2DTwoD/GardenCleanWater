#include "common_for_tasks.h"

extern Sequence *queue[];
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;
extern Coil D4;
extern Coil M7;
extern uint8_t CHBstep;
static const uint8_t numOfTanks = 3; 

void pushSeqInQueue(Sequence *seq){
	for(uint8_t i = 0; i < numOfTanks; i++){
		if(i == numOfTanks - 1){
			queue[i] = seq;
		} else {
			queue[i] = queue[i + 1];
		}
	}
}

Sequence* getSeqFromQueue(){
	for(uint8_t i = 0; i < numOfTanks; i++){
		if(queue[i] != nullptr){
			return queue[i];
		}
	}
	return nullptr;
}

void deleteSeqFromQueue(Sequence *seq){
	for(uint8_t i = 0; i < numOfTanks; i++){
		if(queue[i] == seq){
			queue[i] = nullptr;
			return;
		}
	}
}

void resetCHBsteps(){
	CHBs0.reset();
	CHBs1.reset();
	CHBs2.reset();
	D4 = false;
	M7 = false;
	CHBstep = 0;
}