
#ifndef player_h
#define player_h

#include <stdio.h>
#include "deck.h"
#include "board.h"


class Player {
    
    public:
        Player(Board * b);
        void takeTurn();        // draw tile from the deck, place it, maybe place a meeple
        
    private:
        int score;
        int meeplesAvailable;
        Board * theBoard; 
};








#endif /* player_h */
