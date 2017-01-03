#include "lake.h"
#include "regs.h"

Lake::Lake() {
	id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;

    
    hasDeer = false;
    hasBoar = false;
    hasBuffalo = false;
    hasCroc = false;
    hasGoat = false;
    hasMeep = false;
    isCompleted = false;
}

Lake::~Lake() {
}

void Lake::setId(int id) {
	this->id = id;			
}

int Lake::getId() {
	return id;			
}

void Lake::addMeeple( int playerID ) {
    if( playerID == 1) {
        num_tigers_p1++;
    }
    else if (playerID == 2) {
        num_tigers_p2++;
    }
}

int Lake::getOwner() {
    
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

bool Lake::hasMeeple() {
    return (num_tigers_p1 + num_tigers_p2) > 0;
}

bool Lake::isComplete() {
    return (edgeConnects == 0);
}

void Lake::clearState() {
    id = 0;				 // not part of any jungle
    edgeConnects = 0;
    preyCount = 0;
    num_tigers_p1 = 0;
    num_tigers_p2 = 0;
    numTiles = 0;
    hasDeer = false;
    hasBoar = false;
    hasBuffalo = false;
}
