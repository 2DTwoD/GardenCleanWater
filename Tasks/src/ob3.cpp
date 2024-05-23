#include "all_tasks.h"

extern uint8_t OB3step;
extern Sequence OB3s0;
extern SequenceDelayed OB3s1;
extern SequenceDelayed OB3s2;
extern Sequence OB3s3;
extern SequenceDelayed OB3s4;
extern PulseInterrapt OB3s4MeTimer;
extern Sequence OB3s5;

extern Sequence CHBs2;

extern SimpleInputDelayed B3;
extern SimpleInputDelayed H3;
extern Coil C3;
extern Coil O3;
extern Coil D3;
extern CoilPulse M3;
extern Coil Me3;

static void resetAllSteps(){
	OB3s0.reset();
	OB3s1.reset();
	OB3s2.reset();
	OB3s3.reset();
	OB3s4.reset();
	OB3s5.reset();
	C3 = false;
	O3 = false;
	D3 = false;
	M3 = false;
	Me3 = false;
}

void OB3Task(void *pvParameters){
	resetAllSteps();
	while(1){
		OB3s4MeTimer = OB3s4.active();
		if(OB3s4.finishedImpulse()){
			pushSeqInQueue(&OB3s5);
		}
		switch(OB3step){
			case 0:
				OB3s0.start(true);
				OB3s0.finish(H3.isNotActive());
				C3 = false;
				M3 = false;
				Me3 = false;
				break;
			case 1:
				OB3s1.start(true);
				C3 = false;
				O3 = false;
				D3 = OB3s1.started();
				M3 = false;
				Me3 = false;
				break;
			case 2:
				OB3s2.start(true);
				C3 = OB3s2.started();
				O3 = false;
				D3 = OB3s2.started();
				M3 = false;
				Me3 = false;
				break;
			case 3:
				OB3s3.start(true);
				OB3s3.finish(B3.isActive());
				C3 = OB3s3.started();
				O3 = false;
				D3 = false;
				M3 = OB3s3.started();
				Me3 = OB3s3.started();
				break;
			case 4:
				OB3s4.start(true);
				C3 = false;
				O3 = false;
				D3 = false;
				M3 = false;
				Me3 = OB3s4MeTimer.get();
				break;
			case 5:
				OB3s5.lock(CHBs2.locked());
				OB3s5.finish(H3.isNotActive());
				C3 = false;
				O3 = OB3s5.started();
				D3 = false;
				M3 = false;
				Me3 = false;
				break;
			default:
				OB3step = 0;
				deleteSeqFromQueue(&OB3s5);
				resetCHBsteps();
				resetAllSteps();
		}
		vTaskDelay(1);
	}
}

