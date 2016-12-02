#ifndef board_h
#define board_h

#include <stdio.h>
#include <vector>
#include "card.h"
#include "deck.h"
#include "trail.h"
#include "lake.h"
#include "jungle.h"
#include "regs.h"

#define ROWS  155 //MAXCARDS*2+1
#define COLS  155 //MAXCARDS*2+1

class Board {
    
public:
    Board(Card * card, int x, int y, int orientation);                            // board constructor
    int xy_to_ji(int input, char ji);
    void printBoard();                  // print the state of the board
    void updatePossibleMoves(Card * card);         // update valid moves array
    bool checkIfFits(int i, int j, Card * card );     // check if a given card fits at a given location
    bool placeCard(int x, int y, Card * card, int playerID, int zone);        // place a card onto the board
    bool * getPossibleMoves();
    bool checkPossibleMove(int x, int y);
    bool isPossibleMove();
    int getOrient(int x, int y);


    int numJungles, numTrails, numLakes;
  
    Jungle * jungles;
    Trail * trails;
    Lake * lakes;
    
    void printCardRegions(int i, int j);
    void printFeatures();
    
    int firstI;
    int firstJ;
    int firstROT;

    int min_i = ROWS-1;
    int min_j = COLS-1;

    int max_i = 0;
    int max_j = 0;
        
private:
    Card ** board;                    // will point to 2D array of Cards a.k.a. the board
    bool possibleMoves[ROWS][COLS];   // 2D array which holds valid moves
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
