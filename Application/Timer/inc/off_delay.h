#ifndef OFF_DELAY_H
#define OFF_DELAY_H
#include "stdint.h"
#include "common_timer.h"

class OffDelay: public IUpdated1ms {
	private:
		bool startFlag;
		CommonTimer *timer = nullptr;
	public:
		OffDelay(uint32_t period);
		~OffDelay();
		void update1ms() override;
		void set(bool value);
		bool get();
		void reset();
		OffDelay& operator=(bool value);
};

#endif //OFF_DELAY_H