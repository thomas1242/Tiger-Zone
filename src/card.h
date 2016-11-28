

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
    void edgeclone(Edge* output, Edge* input);
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


    
    // a card can have...
    Jungle * j1, * j2, * j3, * j4;          // up to 4 jungles
    Trail  * t1, * t2, * t3, * t4;          // up to 4 trails
    Lake   * l1, * l2;                      // up to 2 lakes
    
    Edge * topEdge;
    Edge * rightEdge;
    Edge * botEdge;
    Edge * leftEdge;
};



#endif /* card_hpp */
