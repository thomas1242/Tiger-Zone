

#ifndef player_h
#define player_h


#include "board.h"


class Player {
    
public:
    Player(Board * b);
    void takeCard(Card* input);
    bool takeTurn(int i, int j, int orientation);  // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getTigers();
    Card * getCard();   // for GUI
    
    
private:
    int score;
    int tigersAvailable;
    Board * theBoard;
    Card * currCard;
};





#endif 
