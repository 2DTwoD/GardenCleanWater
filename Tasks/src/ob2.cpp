#include "all_tasks.h"

extern uint8_t OB2step;
extern Sequence OB2s0;
extern SequenceDelayed OB2s1;
extern SequenceDelayed OB2s2;
extern Sequence OB2s3;
extern SequenceDelayed OB2s4;
extern Pulse OB2s4MeTimer;
extern Sequence OB2s5;

extern SimpleInputDelayed B2;
extern SimpleInputDelayed H2;
extern Coil C2;
extern Coil O2;
extern Coil D2;
extern CoilPulse M2;
extern Coil Me2;
extern SimpleInputDelayed S4;

static void resetAllSteps(){
	OB2s0.reset();
	OB2s1.reset();
	OB2s2.reset();
	OB2s3.reset();
	OB2s4.reset();
	OB2s5.reset();
	C2 = false;
	O2 = false;
	D2 = false;
	M2 = false;
	Me2 = false;
}

void OB2Task(void *pvParameters){
	resetAllSteps();
	while(1){
		OB2s4MeTimer = OB2s4.started();
		if(OB2s4.finishedImpulse()){
			pushSeqInQueue(&OB2s5);
		}
		switch(OB2step){
			case 0:
				OB2s0.start(true);
				OB2s0.finish(H2.isNotActive());
				C2 = false;
				M2 = false;
				Me2 = false;
				break;
			case 1:
				OB2s1.start(true);
				C2 = false;
				O2 = false;
				D2 = OB2s1.started();
				M2 = false;
				Me2 = false;
				break;
			case 2:
				OB2s2.start(true);
				C2 = OB2s2.started();
				O2 = false;
				D2 = OB2s2.started();
				M2 = false;
				Me2 = false;
				break;
			case 3:
				OB2s3.start(true);
				OB2s3.finish(B2.isActive());
				C2 = OB2s3.started();
				O2 = false;
				D2 = false;
				M2 = OB2s3.started();
				Me2 = OB2s3.started();
				break;
			case 4:
				OB2s4.start(true);
				C2 = false;
				O2 = false;
				D2 = false;
				M2 = false;
				Me2 = OB2s4MeTimer.get();
				break;
			case 5:
				OB2s5.lock(S4.isActive());
				OB2s5.finish(H2.isNotActive());
				C2 = false;
				O2 = OB2s5.started();
				D2 = false;
				M2 = false;
				Me2 = false;
				break;
			default:
				OB2step = 0;
				deleteSeqFromQueue(&OB2s5);
				resetCHBsteps();
				resetAllSteps();
		}
		vTaskDelay(1);
	}
}

