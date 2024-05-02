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
			out = (maxOut - minOut) * (in - minIn) / (maxIn - minIn) + minOut;
		}
		R get(){
			return out;
		}
		Scale<T, R>& operator=(T value){
			set(value);
			return *this;
		}
};

#endif //_SCALE_H
