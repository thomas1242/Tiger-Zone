#include "main.h"
#include "card.h"
#ifndef Board_h
#define Board_h

#define boardsize decksize*2+1		// variable for board length;

class Board {

public:
	Card* matrix[boardlength][boardlength];
    Board();
    int citycount;
    int fieldcount;
    int roadcount;
    void markavail();
    bool checkspace();
    bool place();
    void printBoard();
    
private:
    
};



#endif
