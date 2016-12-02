

#ifndef game_h
#define game_h


#include "board.h"
#include "player.h"
#include <string>

#define OFF 0
#define ON  1


class Game {
    
private:
    Board * board;
    Deck * deck;
    Player * player_one;
    Player * player_two;
    bool current_turn;          // true if one's turn, false if two's turn
    bool isActive;              // is game over
    
public:
    Game(Card *tile, int x, int y, int orientation);
    ~Game();
    int convertID(string str);
    void giveCard(string ID, Input *in);
    void giveTurn(int i, int j);
    void startGame();
    void endGame();
    bool status();
    Board * getBoard();
    int getCurrCardID();
    void rotateCard();
    Player * getCurrPlayer();
    bool getCurrTurn();
    int getScore( bool player );
    int getMeeples( bool player );
    void printBoard();
    Card * getCurrCard();   // for GUI
    Deck * getDeck();
    void setStartingPlayer(bool us);
    
    
};






#endif /* game_hpp */
