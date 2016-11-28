

#ifndef game_h
#define game_h


#include "board.h"
#include "player.h"
//#include "inout.h"


#define OFF 0
#define ON  1


class Game {
    
public:
    Board * board;
    Deck * deck;
    Player * player_one;
    Player * player_two;
    bool current_turn;          // true if one's turn, false if two's turn
    bool isActive;              // is game over
    
    Game();
    ~Game();
    void giveCard();
    void giveTurn(int i, int j, int orientation);
    void startGame();
    void endGame();
    bool status();
    Board * getBoard();
    int getCurrCardID();
    void rotateCard();
    Player * getCurrPlayer();
    bool getCurrTurn();
    int getScore( bool player );
    int getTigers( bool player );
    void printBoard();
    Card * getCurrCard();   // for GUI
    Deck * getDeck();
    
    
    
};






#endif /* game_hpp */
