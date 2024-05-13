#ifndef _SCALE_H
#define _SCALE_H

#include "stdint.h"
#include "interfaces.h"
#include "common.h"

template<typename T, typename R>
class Scale{
	private:
		T in;
		T minIn;
		T maxIn;
		R out;
		R minOut;
		R maxOut;
	public:
		Scale(T minIn, T maxIn, R minOut, R maxOut): minIn(minIn), maxIn(maxIn), minOut(minOut), maxOut(maxOut){
		}
		void set(T value){
			in = limit(value, minIn, maxIn);
			update();
		}
		R get(){
			return out;
		}
		void update(){
			out = (maxOut - minOut) * (in - minIn) / (maxIn - minIn) + minOut;
		}
		Scale<T, R>& operator=(T value){
			set(value);
			return *this;
		}
		T *const getInRef(){
			return &in;
		}
		R *const getOutRef(){
			return &out;
		}
};

#endif //_SCALE_H
