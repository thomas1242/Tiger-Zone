

#ifndef player_h
#define player_h


#include "board.h"


class Player {
    
public:
    Player(Board * b, Deck * d);
    void takeCard();
    bool takeTurn(int i, int j);        // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getMeeples();
    Card * getCard();   // for GUI
    
    
private:
    int score;
    int meeplesAvailable;
    Board * theBoard;
    Deck * theDeck;
    Card * currCard;
};





#endif 
