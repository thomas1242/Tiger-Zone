

#ifndef card_h
#define card_h

#include <stdio.h>



class Card {
    
    private:
        int id;                         	           // card identifier: what type of tile is this
        
        char top, bot, left, right;     	           // l = lake, g = game-trail, j = jungle
        char T_L, T_R, B_L, B_R;                       // corner tiles
        char mid;
        int orientation;    // degreees rotated clockwise, initally 0
    
    public:
        bool isfiller;		// true only on a filler card (possible move on board)
        bool isden;         // true if it's a den
        bool endtrail;      // true if game-trails end at tile

        char a_top, a_bot, a_left, a_right;	// Available spaces, same convention as tblr. Filler only.
        									// Public so other classes can easily change these
        Card();             // construct null card ( id = 0 ). need this constructor for our board constructor
        Card(int id);       // construct a Card a.k.a. an instance of a tile from the deck
        void rotate();      // rotate card 90 degress clockwise
        void assignSides(int id);
        void printCard();
    
        char getTop();  // functions so other classes can have controlled access to private variables
        char getBot();
        char getRight();
        char getLeft();
        
        char getT_L();
        char getT_R();
        char getB_L();
        char getB_R();
        char getMid();


        int getId();
        int getOrient( );
    
};





#endif /* card_hpp */
