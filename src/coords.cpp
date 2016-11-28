#include "coords.h"

bool Coords::operator==(const Coords other) {
    if(this->icoord == other.icoord &&
    	this->jcoord == other.jcoord) {
    	return true;
    }
    else {
        return false;
    }
}

Coords::Coords() {
    icoord = 0;
    jcoord = 0;
}

Coords::Coords(int i, int j) {
    icoord = i;
    jcoord = j;
}

Coords::~Coords() {
    
}