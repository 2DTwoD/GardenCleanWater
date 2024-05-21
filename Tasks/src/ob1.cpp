#include "all_tasks.h"

extern uint8_t OB1step;
extern Sequence OB1s0;
extern SequenceDelayed OB1s1;
extern SequenceDelayed OB1s2;
extern Sequence OB1s3;
extern SequenceDelayed OB1s4;
extern Sequence OB1s5;
extern Pulse OB1s4MeTimer;

extern SimpleInputDelayed B1;
extern SimpleInputDelayed H1;
extern Coil C1;
extern Coil O1;
extern Coil D1;
extern CoilPulse M1;
extern Coil Me1;
extern SimpleInputDelayed S4;

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
		OB1s4MeTimer = OB1s4.started();
		switch(OB1step){
			case 0:
				OB1s0.slfSet(true, false, H1.isActive());
				C1 = false;
				M1 = false;
				Me1 = false;
				break;
			case 1:
				OB1s1.slfSet(true, false, false);
				C1 = false;
				O1 = false;
				D1 = OB1s1.started();
				M1 = false;
				Me1 = false;
				break;
			case 2:
				OB1s2.slfSet(true, false, false);
				C1 = OB1s2.started();
				O1 = false;
				D1 = OB1s2.started();
				M1 = false;
				Me1 = false;
				break;
			case 3:
				OB1s3.slfSet(true, false, B1.isActive());
				C1 = OB1s3.started();
				O1 = false;
				D1 = false;
				M1 = OB1s3.started();
				Me1 = OB1s3.started();
				break;
			case 4:
				OB1s4.slfSet(true, false, false);
				C1 = false;
				O1 = false;
				D1 = false;
				M1 = false;
				Me1 = OB1s4MeTimer.get();
				if(OB1s4.finished()){
					pushSeqInQueue(&OB1s5);
				}
				break;
			case 5:
				OB1s5.slfSet(false, S4.isActive(), H1.isNotActive());
				C1 = false;
				O1 = OB1s5.started();
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

