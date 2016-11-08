#ifndef board_h
#define board_h

#include <stdio.h>
#include "card.h"


class Board {
    
    public:
        Board();                // board constructer
        void printBoard();      // print the state of the board
    
    private:
        Card ** board;   // pointer to an array of Card pointers a.k.a. will point to 2D array of Card objects a.k.a. the board
    
};





#endif /* board_hpp */
