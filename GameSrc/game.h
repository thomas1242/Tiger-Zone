

#ifndef game_h
#define game_h


#include "board.h"

#define OFF 0
#define ON  1


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



class Game {
    
private:
    Board * board;
    Deck * deck;
    Player * player_one;
    Player * player_two;
    bool current_turn;          // true if one's turn, false if two's turn
    bool isActive;              // is game over
    
public:
    Game();
    ~Game();
    void giveCard();
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
    
    
    
};






#endif /* game_hpp */
