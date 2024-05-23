#include "all_tasks.h"

extern uint8_t OB1step;
extern Sequence OB1s0;
extern SequenceDelayed OB1s1;
extern SequenceDelayed OB1s2;
extern Sequence OB1s3;
extern SequenceDelayed OB1s4;
extern PulseInterrapt OB1s4MeTimer;
extern Sequence OB1s5;

extern Sequence CHBs2;

extern SimpleInputDelayed B1;
extern SimpleInputDelayed H1;
extern Coil C1;
extern Coil O1;
extern Coil D1;
extern CoilPulse M1;
extern Coil Me1;

static void resetAllSteps(){
	OB1s0.reset();
	OB1s1.reset();
	OB1s2.reset();
	OB1s3.reset();
	OB1s4.reset();
	OB1s5.reset();
	C1 = false;
	O1 = false;
	D1 = false;
	M1 = false;
	Me1 = false;
}

void OB1Task(void *pvParameters){
	resetAllSteps();
	while(1){
		OB1s4MeTimer = OB1s4.active();
		if(OB1s4.finishedImpulse()){
			pushSeqInQueue(&OB1s5);
		}
		switch(OB1step){
			case 0:
				OB1s0.start(true);
				OB1s0.finish(H1.isNotActive());
				C1 = false;
				M1 = false;
				Me1 = false;
				break;
			case 1:
				OB1s1.start(true);
				C1 = false;
				O1 = false;
				D1 = OB1s1.active();
				M1 = false;
				Me1 = false;
				break;
			case 2:
				OB1s2.start(true);
				C1 = OB1s2.active();
				O1 = false;
				D1 = OB1s2.active();
				M1 = false;
				Me1 = false;
				break;
			case 3:
				OB1s3.start(true);
				OB1s3.finish(B1.isActive());
				C1 = OB1s3.active();
				O1 = false;
				D1 = false;
				M1 = OB1s3.active();
				Me1 = OB1s3.active();
				break;
			case 4:
				OB1s4.start(true);
				C1 = false;
				O1 = false;
				D1 = false;
				M1 = false;
				Me1 = OB1s4MeTimer.get();
				break;
			case 5:
				OB1s5.lock(CHBs2.locked());
				OB1s5.finish(H1.isNotActive());
				C1 = false;
				O1 = OB1s5.active();
				D1 = false;
				M1 = false;
				Me1 = false;
				break;
			default:
				OB1step = 0;
				deleteSeqFromQueue(&OB1s5);
				resetCHBsteps();
				resetAllSteps();
		}
		vTaskDelay(1);
	}
}

