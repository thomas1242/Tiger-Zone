

#ifndef card_h
#define card_h

#include <stdio.h>
#include "edge.h"
#include "trail.h"
#include "jungle.h"
#include "lake.h"
#include <string>
using namespace std;




class Card {
    
private:
    
    string cardID;
    int id;             // card identifier: what type of tile is this
    int orientation;    // degreees rotated clockwise, initally 0
    

    

    
    char mid; // might not need this
    
    
public:
    Card();             // construct null card ( id = 0 ). need this constructor for our board constructor
    Card(int id);       // construct a Card a.k.a. an instance of a tile from the deck
    void rotate();      // rotate card 90 degress clockwise
    void assignSides();
    void assignCardID();
    void printCard();
    
    char getTop();  // functions so other classes can have controlled access to private variables
    char getBot();
    char getRight();
    char getLeft();
    char getMid();
    
    int getId();
    int getOrient( );
    string getCardID();
    void connectEdgestoCard();
    void reConnect();
    void assignCloseID();
    void printCells(int & L1, int & L2, int & J1, int & J2, int & J3, int & J4, int & T1, int & T2, int & T3, int & T4);
    void setValue( int & oldVal, int newVal );
    
    // a card can have...
    Jungle * j1, * j2, * j3, * j4;          // up to 4 jungles
    Trail  * t1, * t2, * t3, * t4;          // up to 4 trails
    Lake   * l1, * l2;                      // up to 2 lakes
    
    Edge * topEdge;
    Edge * rightEdge;
    Edge * botEdge;
    Edge * leftEdge;
    
    string cardMatrix[3][3];    // 3x3 card matrix for meeple placement
    
    
    
    int extendID;    // -1 no card, 0 if extending lake, 1 if closing lake, 2 if closing trail, 3 if closing trail&lake
    
    
};



#endif /* card_hpp */
