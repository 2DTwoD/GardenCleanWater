#include "all_tasks.h"

extern uint8_t OB1step;
extern Sequence OB1s0;
extern Sequence OB1s1;
extern Sequence OB1s2;
extern Sequence OB1s3;
extern Sequence OB1s4;
extern Sequence OB1s5;
extern OnDelay OB1s1Delay;
extern OnDelay OB1s2Delay;
extern OnDelay OB1s4Delay;
extern CommonTimer OB1s4MeTimer;

extern SimpleInputDelayed B1;
extern SimpleInputDelayed H1;
extern Coil C1;
extern Coil O1;
extern Coil D1;
extern CoilPulse M1;
extern Coil Me1;
extern SimpleInputDelayed S4;

void resetAllSteps(){
	OB1s0.reset();
	OB1s1.reset();
	OB1s2.reset();
	OB1s3.reset();
	OB1s4.reset();
	OB1s5.reset();
}

static void setCoils(bool c, bool o, bool d, bool m, bool me){
	C1 = c;
	O1 = o;
	D1 = d;
	M1 = m;
	Me1 = me;
}

void OB1Task(void *pvParameters){
	resetAllSteps();
	while(1){
		OB1s1Delay = OB1s1.started();
		OB1s2Delay = OB1s2.started();
		OB1s4Delay = OB1s4.started();
		OB1s4MeTimer = OB1s4.started();
		switch(OB1step){
			case 0:
				OB1s0.slfSet(true, false, H1.isActive());
				C1 = false;
				M1 = false;
				Me1 = false;
				break;
			case 1:
				OB1s1.slfSet(true, false, OB1s1Delay.get());
				setCoils(false, false, OB1s1.started(), false, false);
				break;
			case 2:
				OB1s2.slfSet(true, false, OB1s2Delay.get());
				setCoils(OB1s2.started(), false, OB1s2.started(), false, false);
				break;
			case 3:
				OB1s3.slfSet(true, false, B1.isActive());
				setCoils(OB1s3.started(), false, false, OB1s3.started(), OB1s3.started());
				break;
			case 4:
				OB1s4.slfSet(true, false, OB1s4Delay.get());
				setCoils(false, false, false, false, OB1s4MeTimer.inWork());
				if(OB1s4.finished()){
					pushSeqInQueue(&OB1s5);
				}
				break;
			case 5:
				OB1s5.slfSet(false, S4.isActive(), H1.isNotActive());
				setCoils(false, OB1s5.started(), false, false, false);
				break;
			default:
				OB1step = 0;
		}
		vTaskDelay(1);
	}
}

