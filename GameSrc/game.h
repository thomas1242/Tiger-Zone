

#ifndef game_h
#define game_h

#include <stdio.h>
#include "card.h"
#include "board.h"
#include "player.h"
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


    
};






#endif /* game_hpp */
