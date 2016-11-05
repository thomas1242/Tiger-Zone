#include "main.h"
#include "card.h"
#ifndef Board_h
#define Board_h


class Board {

public:
	card* board[size*2+1][size*2+1];
    Board();
    void printBoard();
    
private:
    
};



#endif
