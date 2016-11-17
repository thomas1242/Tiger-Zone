
#ifndef player_h
#define player_h

#include <stdio.h>
#include "deck.h"
#include "board.h"


class Player {
    
    public:
        Player(Board * b, Deck * d);
        Card * takeCard();
        bool takeTurn(int i, int j);        // draw tile from the deck, place it, maybe place a meeple
        void drawCard();
        void rotateCard();
        bool hasCard;
        int getCardId();    // for GUI
        int getScore();
        int getMeeples();

    private:
        int score;
        int meeplesAvailable;
        Board * theBoard;
        Deck * theDeck;
        Card * currCard;
};








#endif /* player_h */
