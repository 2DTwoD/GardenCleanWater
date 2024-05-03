#include "moving_avg.h"

MovAvg::MovAvg(uint8_t size){
	this->size = max((uint8_t) 1, size);
	row = new float[size];
	memset(row, 0, size);
	pos = 0;
}
MovAvg::~MovAvg(){
	delete row;
}
void MovAvg::set(float value){
	in = value;
	updateSomewhere();
}
float MovAvg::get(){
	return out;
}
void MovAvg::updateSomewhere(){
	row[pos] = in;
	pos++;
	if(pos >=size){
		pos = 0;
	}
	out = 0.0f;
	for(uint8_t i = 0; i < size; i++){
		out += row[i];
	}
	out /= size;
}
float *const MovAvg::getInRef(){
	return &in;
}
float *const MovAvg::getOutRef(){
	return &out;
}