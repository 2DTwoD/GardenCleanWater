#ifndef SWITCH_DELAY_H
#define SWITCH_DELAY_H
#include "interfaces.h"
#include "common_timer.h"

class SwitchDelay: public CommonTimer{
	private:
		ISwitch *swtch;
	public:
		SwitchDelay(ISwitch *swtch, uint16_t period);
		bool started() override;
};
#endif //SWITCH_DELAY_H