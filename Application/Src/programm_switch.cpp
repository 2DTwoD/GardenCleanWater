#include "programm_switch.h"

void ProgrammSwitch::set(){
	status = true;
}

void ProgrammSwitch::reset(){
	status = false;
}
	
void ProgrammSwitch::setValue(bool value){
	status = value;
}

bool ProgrammSwitch::isActive(){
	return status;
}

ProgrammSwitch& ProgrammSwitch::operator=(bool value){
	setValue(value);
	return *this;
}