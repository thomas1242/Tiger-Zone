//#include "lake.h"
#include "regs.h"


Lake::Lake() {
	id = 0;				 // not part of any jungle
}

Lake::~Lake() {
}

void Lake::setId(int id) {
	this->id = id;			
}

int Lake::getId() {
	return id;			
}
