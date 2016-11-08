

#ifndef card_h
#define card_h

#include <stdio.h>



class Card {
    
    private:
        int id;                         // card identifier: what type of tile is this
        char top, bot, left, right;     // c = city, r = road, f= field
        
    public:
        Card();             // construct null card ( id = 0 ). need this constructor for our board constructor
        Card(int id);       // construct a Card a.k.a. an instance of a tile from the deck
        void rotate();      // rotate card 90 degress clockwise
        void assignSides(int id);
        void printCard();
    
        char getTop();  // functions so other classes can have controlled access to private variables
        char getBot();
        char getRight();
        char getLeft();
        char getId();
    
};





#endif /* card_hpp */
