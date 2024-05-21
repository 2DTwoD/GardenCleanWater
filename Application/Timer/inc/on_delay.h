#ifndef ON_DELAY_H
#define ON_DELAY_H
#include "stdint.h"
#include "common_timer.h"

class OnDelay: private CommonTimer, public IUpdated1ms {
	public:
		OnDelay(uint32_t period);
		void update1ms() override;
		void set(bool value);
		bool get();
		void reset();
		OnDelay& operator=(bool value);
};

#endif //ON_DELAY_H