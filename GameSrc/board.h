#ifndef board_h
#define board_h

#include <stdio.h>
#include <list>
#include "card.h"
#include "deck.h"
#include "moves.h"
#include "coords.h"

#define ROWS  11 //MAXCARDS*2+1
#define COLS  11 //MAXCARDS*2+1

class Board {
public:

        Board(Card* card);                           		// board constructor
        void printBoard();                  				// print the state of the board
        bool checkIfFits(int i, int j, Card * card );    	// check if a given card fits at a given location
        void markavail(int xcoord, int ycoord, Card* card); // Marks available tile
        bool placeCard(int i, int j, Card* card);      	    // place a card onto the board
        Card getCard(int i, int j);
        bool updatePossibleMoves(Card * card);
        list<Moves> possibleMoves;      // 2D array which holds valid moves

    private:
        Card ** board;                  // will point to 2D array of Cards a.k.a. the board
        list<Coords> markedtiles;        // Marked tiles can be possible moves
};


#endif /* board_hpp */
