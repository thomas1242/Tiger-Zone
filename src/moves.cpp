#include "moves.h"

bool Moves::operator==(const Moves other) {
    if(this->icoord == other.icoord &&
        this->jcoord == other.jcoord) {
        for(int i = 0; i < 4; i++) {
            if(this->possibleorientations[i] != other.possibleorientations[i]) {
                return false;
            }
        }
        return true;
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
