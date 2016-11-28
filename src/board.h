#ifndef board_h
#define board_h

#include <stdio.h>
#include <vector>
#include <list>
#include "card.h"
#include "deck.h"
#include "trail.h"
#include "lake.h"
#include "jungle.h"
#include "regs.h"
#include "moves.h"
#include "coords.h"


class Board {
    
public:
    Board(Card* card);                            // board constructer
    void printBoard();                  // print the state of the board
    bool checkIfFits(int i, int j, Card * card );     // check if a given card fits at a given location
    bool placeCard(int i, int j, Card * card, int rotations, 
                    int playerID, int zone);        // place a card onto the board
    void markavail(int xcoord, int ycoord, Card* card); // Marks available tile
    void updatePossibleMoves(Card * card);         // update valid moves array
    void refreshPossibleMoves();
    Card getCard(int i, int j);
    list<Moves*> possibleMoves; 

    int numJungles, numTrails, numLakes;
  
    Jungle * jungles;
    Trail * trails;
    Lake * lakes;
    
    void printCardRegions(int i, int j);
    void printFeatures();

private:
    Card ** board;                    // will point to 2D array of Cards a.k.a. the board
    list<Coords*> markedtiles;        // Marked tiles can be possible moves
};

//struct Lakes {
//    int lakeNum;
//    bool owned; //0 - no; 1 - you; 2 - enemy
//    int edges;
//    vector<pair<int, int> > coords;
//    vector<int> orientations;
//};
//struct Lakes availLakes[35];
//
//struct Trails {
//    int trailNum;
//    bool owned; //0 - no; 1 - you; 2 - enemy
//    int edges;
//    vector<pair<int, int> > coords;
//    vector<int> orientations;
//};
//struct Trails availTrails[35];

#endif /* board_hpp */
