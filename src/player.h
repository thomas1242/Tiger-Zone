
#ifndef player_h
#define player_h

#include <stdio.h>
#include "deck.h"
#include "board.h"


class Player {
    
    public:
<<<<<<< HEAD
        Player();
        void takeTurn();        // draw tile from the deck, place it, maybe place a meeple
        
=======
        Player(Board * b);
        bool takeTurn(int i, int j);        // draw tile from the deck, place it, maybe place a meeple
        void drawCard();
        void rotateCard();
        bool hasCard;
        int getCardId();    // for GUI
        Card * getCard();
        int getScore();
        int getMeeples();

    
>>>>>>> sfmlBranch
    private:
        int score;
        int meeplesAvailable;
        Board * theBoard;
<<<<<<< HEAD
        Deck * theDeck;
=======
        Card * currCard;
    
>>>>>>> sfmlBranch
};


#endif /* player_h */
