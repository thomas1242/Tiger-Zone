#ifndef board_h
#define board_h

#include <stdio.h>
#include <list>
#include "card.h"
#include "deck.h"

#define ROWS  11 //MAXCARDS*2+1
#define COLS  11 //MAXCARDS*2+1

class Coords {
public:    
    int icoord;
    int jcoord;

    Coords(int i, int j);
    ~Coords();
};

class Moves {
public:    
    int icoord;
    int jcoord;
    bool possibleorientations[4];    // 0=0, 1=90, 2=180, 3=270

    Moves(int i, int j);
    ~Moves();
};


class Board {
public:

        Board(Card* card);                           		// board constructor
        void printBoard();                  				// print the state of the board
        bool checkIfFits(int i, int j, Card * card );    	// check if a given card fits at a given location
        void markavail(int xcoord, int ycoord, Card* card); // Marks available tile
        bool placeCard(int i, int j, Card* card);      	    // place a card onto the board
        Card getCard(int i, int j);

    
    private:
        Card ** board;                  // will point to 2D array of Cards a.k.a. the board
        list<Moves> possibleMoves;      // 2D array which holds valid moves
        list<Coords> markedtiles;        // Marked tiles can be possible moves
};


#endif /* board_hpp */
