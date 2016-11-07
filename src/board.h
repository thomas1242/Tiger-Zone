#include "main.h"
#include "card.h"
#ifndef Board_h
#define Board_h


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
