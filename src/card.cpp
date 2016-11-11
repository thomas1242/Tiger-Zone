#include <iostream>
#include "card.h"
using namespace std;


Card::Card() {
    id = -1;            // set id = -1, this card is an instance of open space on the board
    top = 'o';          // this card is free space
    bot = 'o';
    left = 'o';
    right = 'o';
    orientation = 0;
}

Card::Card(int id) {
    this->id = id;          // set this cards id
    assignSides(id);        // set default sides corresponding to this card type
    orientation = 0;
}

void Card::rotate() {   // rotate card 90 degrees clockwise
    char temp = right;
    right = top;
    top = left;
    left = bot;
    bot = temp;
    orientation = (orientation + 90) % 360; 
}

void Card::printCard() {
    cout << "Card id = " << id << endl;
    // ---------------------------------
    cout << " "  << top << " " << endl;
    cout << left << " " << right << endl;
    cout << " "  << bot << " " << endl;
}

void Card::assignSides(int id) {
    
    // mark top of card depending on card id
    if(id == 17 || id == 2 || id == 1 || id == 23 || id == 10 || id == 13) {          // card with field top
        top = 'f';
    }
    else if (id == 7 || id == 16) {                                                     // card with road top
        top = 'r';
    }
    else {                                                                              // card with city top
        top = 'c';
    }
    
    // mark right of card depending on card id
    if(id == 18 || id == 5 || id == 19 || id == 9 || id == 20 || id == 1 || id == 23) {          // card with city right
        right = 'c';
    }
    else if (id == 15 || id == 22 || id == 14 || id == 0 || id == 3 || id == 13 || id == 16) {                          // card with road right
        right = 'r';
    }
    else {                                                                                      // card with field right
        right = 'f';
    }
    
    // mark bot of card depending on card id
    if(id == 18 || id == 6) {                                                           // card with city bot
        bot = 'c';
    }
    else if (id == 17 || id == 5 || id == 19 || id == 12 || id == 21 || id == 1
             || id == 23 || id == 4 || id == 8 || id == 3) {                            // card with field bot
        bot = 'f';
    }
    else {                                                                              // card with road bot
        bot = 'r';
    }
    
    // mark left of card depending on card id
    if(id == 18 || id == 5 || id == 19 || id == 9 || id == 20 || id == 12
       || id == 21 || id == 15 || id == 22 || id == 1 || id == 23 || id == 4) {          // card with city left
        left = 'c';
    }
    else if (id == 11 || id == 0 || id == 3 || id == 10 || id == 13 || id == 16) {    // card with road left
        left = 'r';
    }
    else {                                                                              // card with field left
        left = 'f';
    }
    
}

char Card::getTop() {
    return top;
}
char Card::getBot() {
    return bot;
}
char Card::getRight() {
    return right;
}
char Card::getLeft() {
    return left;
}
int Card::getId() {
    return id;
}
int Card::getOrient() {
    return orientation;
}

