

#ifndef player_h
#define player_h


//#include "inout.h"
#include "board.h"
#include <string>


class Player {
    
public:
    Player(Board * b, Deck * d, int playerID);


    int convertID(string ID);
   // void takeCard(string strID, Output *out);
    void takeCard( );

    
    bool takeTurn(int i, int j);        // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getMeeples();
    Card * getCard();   // for GUI
    
    int playerID;       // which player is this: player id
    
private:
    int score;
    int meeplesAvailable;
    Board * theBoard;
    Deck * theDeck;
    Card * currCard;
};





#endif 
