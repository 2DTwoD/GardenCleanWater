#include "switch_delay.h"

SwitchDelay::SwitchDelay(ISwitch *swtch, uint16_t period): CommonTimer(period){
	this->swtch = swtch;
}
bool SwitchDelay::started(){
	return CommonTimer::started() || swtch->isActive();
}