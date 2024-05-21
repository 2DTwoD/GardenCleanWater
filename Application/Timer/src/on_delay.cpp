#include "on_delay.h"

OnDelay::OnDelay(uint32_t period): CommonTimer(period){
}
void OnDelay::update1ms(){
	CommonTimer::update();
}
void OnDelay::set(bool value){
	CommonTimer::setStart(value);
}
bool OnDelay::get(){
	return CommonTimer::finished();
}
void OnDelay::reset(){
	CommonTimer::reset();
}
OnDelay& OnDelay::operator=(bool value){
	set(value);
	return *this;
}