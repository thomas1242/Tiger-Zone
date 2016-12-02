

#ifndef player_h
#define player_h


#include "inout.h"
#include "board.h"
#include <string>


class Player {
    
public:
    Player(Board * b, int playerID);


    int convertID(string ID);
    void takeCard(string strID, Input *in);
    bool takeTurn(int x, int y);        // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getTigers();
    Card * getCard();   // for GUI
    
    int playerID;       // which player is this: player id
    
private:
    int score;
    int tigersAvailable;
    Board * theBoard;
    //Deck * theDeck;
    Card * currCard;
};





#endif 
