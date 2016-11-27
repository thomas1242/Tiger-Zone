#include "jungle.h"
#include "regs.h"


Jungle::Jungle() {
	id = 0;				 // not part of any jungle
}

Jungle::~Jungle() {
}

void Jungle::setId(int id) {
	this->id = id;			
}

int Jungle::getId() {
	return id;			
}
