#include "common_for_tasks.h"

extern Sequence *queue[];

void pushSeqInQueue(Sequence *seq){
	for(uint8_t i = 0; i < 3; i++){
		if(i == 2){
			queue[i] = seq;
		} else {
			queue[i] = queue[i + 1];
		}
	}
}

Sequence* getSeqFromQueue(){
	for(uint8_t i = 0; i < 3; i++){
		if(queue[i] != nullptr){
			return queue[i];
		}
	}
	return nullptr;
}

void deleteSeqFromQueue(Sequence *seq){
	for(uint8_t i = 0; i < 3; i++){
		if(queue[i] == seq){
			queue[i] = nullptr;
			return;
		}
	}
}