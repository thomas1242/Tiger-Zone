#include "edge.h"
#include <stdio.h>

Edge::Edge() {
	this->type = 'o';		// open edge
    //setEdgePointers(' ');
}

Edge::Edge(char type) {
	this->type = type;		// J or T or L
    //setEdgePointers(type);
}

Edge::~Edge() {
}

char Edge::getType() {
	return type;			
}

/*void Edge::setEdgePointers(char type) {
        j1 = ;
        j2 = ;
        t1 = ;
        l1 = ;
 */   
//if(type == ' '){
//    }
//    else if( type == 'J'){
//        j1 = new Jungle();
//    }
//    else if( type == 'L'){
//        l1 = new Lake();
//
//    }
//    else if( type == 'T'){
//        t1 = new Trail();
//        j1 = new Jungle();
//        j2 = new Jungle();
//    }
    
