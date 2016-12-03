#include "trail.h"
#include "regs.h"

Trail::Trail() {
    id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;
    hasCroc = false;
}

Trail::~Trail() {
}

void Trail::setId(int id) {
	this->id = id;			
}

int Trail::getId() {
	return id;			
}

void Trail::addMeeple( int playerID ) {
    if( playerID == 1) {
        num_tigers_p1++;
    }
    else if (playerID == 2) {
        num_tigers_p2++;
    }
}

int Trail::getOwner() {
    
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

bool Trail::isComplete() {
    return (edgeConnects == 0);
}

void Trail::clearState() {
    id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;
}
