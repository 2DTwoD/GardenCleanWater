#include "all_tasks.h"

extern uint8_t CHBstep;
extern Sequence CHBs0;
extern Sequence CHBs1;
extern Sequence CHBs2;

extern Sequence OB1s5;

extern SimpleInputDelayed S4;
extern SimpleInputDelayed S5;
extern SimpleInputDelayed S6;
extern Coil D4;
extern Coil M6;
extern Coil M7;

static void setCoils(bool d, bool m){
	D4 = d;
	M7 = m;
}

void CHBTask(void *pvParameters){
	while(1){
		switch(CHBstep){
			case 0:
				CHBs0.slfSet(S5.isNotActive(), false, getSeqFromQueue() != nullptr);
				setCoils(false, false);
				if(CHBs0.finished()){
					getSeqFromQueue()->start(true);
				}
				break;
			case 1:
				CHBs1.slfSet(true, false, false);
				setCoils(CHBs1.started(), false);
				break;
			case 2:
				CHBs2.slfSet(true, S4.isActive(), false);
				setCoils(false, CHBs2.started());
				break;
		}
		M6 = S6.isActive();
		vTaskDelay(1);
	}
}

