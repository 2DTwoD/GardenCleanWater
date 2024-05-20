#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "rf_impulse.h"

class Sequence: private RFimpulse{
	private:
		bool strt;
		bool lck;
		bool fin;
		uint8_t seq_step;
		uint8_t *cur_step_pointer;
		bool isMyStep();
	public:
		Sequence(uint8_t *cur_step_pointer, uint8_t seq_step);
		void reset();
		void start(bool value);
		void lock(bool value);
		void finish(bool value);
		void slfSet(bool strt, bool lck, bool fin);
		bool started();
		bool locked();
		bool finished();
		bool finishedImpulse();
};

#endif //SEQUENCE_H