

#ifndef player_h
#define player_h

//#include "game.h"
#include "inout.h"
#include "board.h"
#include <string>

class Player {
    
public:
    Player(Board * b, Deck * d);
    int convertID(string ID);
    void takeCard(string strID, Output *out);
    bool takeTurn(int i, int j);        // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getMeeples();
    Card * getCard();   // for GUI
    Board * theBoard;
    
private:
    int score;
    int meeplesAvailable;
    
    Deck * theDeck;
    Card * currCard;
};





#endif 
