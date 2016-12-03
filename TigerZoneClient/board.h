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
#include "inout.h"


#define ROWS  155 //MAXCARDS*2+1
#define COLS  155 //MAXCARDS*2+1

class Board {
    
public:
    Board(Card * card, int x, int y, int orientation);                            // board constructer
    void printBoard();                  // print the state of the board
    void updatePossibleMoves(Card * card);         // update valid moves array
    bool checkIfFits(int i, int j, Card * card );     // check if a given card fits at a given location
    bool placeCard(int i, int j, Card * card, int playerID, int zone, bool typeFollower);        // place a card onto the board
    Deck * getDeck();
    bool * getPossibleMoves();
    bool checkPossibleMove(int i, int j);
    bool isPossibleMove();
    Card getCard(int i, int j);
    int getOrient(int i, int j);

    void connectCardtoBoard( int i, int j, Card * card );
    
    void placeMeeple(int playerID, int zone, bool tiger, Card * card);
    void mergeLakes(int l1_id, int l2_id);
    void mergeTrails(int t1_id, int t2_id);
    void mergeJungles(int j1_id, int j2_id);
    
    void incrementEdges(int i, int j, Card * card);

    void scoreMove(Card * card, int playerID);
    void scoreTrail(  Trail *  t , int playerID );
    void scoreLake(   Lake  *  l , int playerID );
    void scoreJungle( Jungle * j , int playerID );
    
    int numJungles, numTrails, numLakes;
  
    Jungle * jungles;
    Trail * trails;
    Lake * lakes;
    
    void printCardRegions(int i, int j);
    void printFeatures();
    int p1_score, p2_score;
    int getScore( bool player );
    void markAdjacentLakes(Card * card);
    void endGameScoring();
    
    void getBestMove();         // based on the current card & board
    
    
    
        
private:
    Card ** board;                    // will point to 2D array of Cards a.k.a. the board
    bool possibleMoves[ROWS][COLS];   // 2D array which holds valid moves
};


#endif /* board_hpp */
