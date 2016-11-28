

#ifndef player_h
#define player_h


#include "board.h"
#include "inout.h"
#include <utility>



class Player {
    
public:
    Player(Board * b, int playerID);
    int ji_to_xy(int input, char id);
    bool underduress();
    void takeCard(Card* input, bool DURESS);
    bool takeTurn(int i, int j, int orientation);        // draw tile from the deck, place it, maybe place a meeple
    void drawCard();
    void rotateCard();
    bool hasCard;
    int getCardId();    // for GUI
    int getScore();
    int getTigers();
    Card * getCard();   // for GUI

    
    int playerID;       // which player is this: player id
    
    int score;
    int tigersAvailable;
    Board * theBoard;
    Card * currCard;
    Output  out;
};





#endif 
