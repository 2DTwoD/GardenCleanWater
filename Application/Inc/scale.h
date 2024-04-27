#ifndef _SCALE_H
#define _SCALE_H

#include "stdint.h"
#include "interfaces.h"
#include "common.h"

template<typename T, typename R>
class Scale: public IUpdated{
	private:
		T in;
		T *inRef;
		T minIn;
		T maxIn;
		R out;
		R *outRef;
		R minOut;
		R maxOut;
	public:
		Scale(T minIn, T maxIn, R minOut, R maxOut, T *inRef = nullptr, R *outRef = nullptr): minIn(minIn), maxIn(maxIn), minOut(minOut), maxOut(maxOut), inRef(inRef), outRef(outRef){
		}
		void update() override {
			if(inRef) in = *inRef;
			in = limit(in, minIn, maxIn);
			out = (maxOut - minOut) * (in - minIn) / (maxIn - minIn) + minOut;
			if(outRef) *outRef = out;
		}
		void setIn(T value){
			in = value;
		}
		void setInUpdate(T value){
			setIn(value);
			update();
		}
		R getOut(){
			return out;
		}
};

#endif //_SCALE_H
