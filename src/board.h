#ifndef board_h
#define board_h

#include <stdio.h>
#include "card.h"
#include "deck.h"


// Kurt - These values should not be hardcoded, and should rely on maximum card count
#define ROWS  MAXCARDS*2+1
#define COLS  MAXCARDS*2+1

class Board {
    
    public:
        Board();                           					// board constructor
        void printBoard();                  				// print the state of the board
        bool checkIfFits(int i, int j, Card * card );    	// check if a given card fits at a given location
        bool placeCard(int i, int j, Card * card);      	// place a card onto the board
        Deck * getDeck();
    
    private:
        Card ** board;                    // will point to 2D array of Cards a.k.a. the board
        bool possibleMoves[ROWS][COLS];   // 2D array which holds valid moves
        Deck * theDeck;					  // Should this be in here or main?
    
};





#endif /* board_hpp */
