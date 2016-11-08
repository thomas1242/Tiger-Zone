#ifndef board_h
#define board_h

#include <stdio.h>
#include "card.h"
#include "deck.h"

#define ROWS  11
#define COLS  11

class Board {
    
    public:
        Board();                            // board constructer
        void printBoard();                  // print the state of the board
        void updatePossibleMoves(Card * card);         // update valid moves array
        bool checkIfFits(int i, int j, Card * card );     // check if a given card fits at a given location
        bool placeCard(int i, int j, Card * card);        // place a card onto the board
        Deck * getDeck();
    
    private:
        Card ** board;                    // will point to 2D array of Cards a.k.a. the board
        bool possibleMoves[ROWS][COLS];   // 2D array which holds valid moves
        Deck * theDeck;
    
};





#endif /* board_hpp */
