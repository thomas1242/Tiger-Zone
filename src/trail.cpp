//#include "trail.h"
#include "regs.h"

Trail::Trail() {
	id = 0;				
}

Trail::~Trail() {
}

void Trail::setId(int id) {
	this->id = id;			
}

int Trail::getId() {
	return id;			
}
