#include "moves.h"

bool Moves::operator == (const Moves &other) const {
    if(icoord == other.icoord &&
        jcoord == other.jcoord) {
        for(int i = 0; i < 4; i++) {
            if(this->possibleorientations[i] != other.possibleorientations[i]) {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

Moves::Moves() {
    icoord = 0;
    jcoord = 0;
    for (int i = 0; i < 4; i++) {
        possibleorientations[i] = 0;
    }
}

Moves::Moves(int i, int j) {
    icoord = i;
    jcoord = j;
    for (int i = 0; i < 4; i++) {
        possibleorientations[i] = 0;
    }
}

Moves::~Moves() {
    
}
