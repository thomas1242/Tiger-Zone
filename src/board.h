#include "main.h"
#include "card.h"
#ifndef Board_h
#define Board_h


class Board {

public:
	Card* board[boardlength][boardlength];
    Board();
    int citycount;
    int fieldcount;
    int roadcount;
    void markavail();
    void place();
    void printBoard();
    
private:
    
};



#endif
