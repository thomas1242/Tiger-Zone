#include "moves.h"

Moves::Moves() {
    icoord = 0;
    jcoord = 0;
    for (int i = 0; i < 4; i++) {
        possibleorientations[i] == 0;
    }
}

Moves::Moves(int i, int j) {
    icoord = i;
    jcoord = j;
    for (int i = 0; i < 4; i++) {
        possibleorientations[i] == 0;
    }
}

Moves::~Moves() {
    
}
