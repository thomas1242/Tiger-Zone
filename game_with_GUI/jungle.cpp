#include "jungle.h"
#include "regs.h"


Jungle::Jungle() {
    id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;
}

Jungle::~Jungle() {
}

void Jungle::setId(int id) {
	this->id = id;			
}

int Jungle::getId() {
	return id;			
}

void Jungle::addMeeple( int playerID ) {
    if( playerID == 1) {
        num_tigers_p1++;
    }
    else if (playerID == 2) {
        num_tigers_p2++;
    }
}

int Jungle::getOwner() {
    
    if(num_tigers_p1 == 0 && num_tigers_p2 == 0) {  // no owner
        return -1;
    }
    else if (num_tigers_p1 == num_tigers_p2) {      // equal ownership
        return 0;
    }
    else if (num_tigers_p1 > num_tigers_p2) {       // player 1 owns
        return 1;
    }
    else {                                          // player 2 owns
        return 2;
    }
}


bool Jungle::isComplete() {
    return (edgeConnects == 0);
}

void Jungle::clearState() {
    id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;
}
