#include <iostream>
#include "card.h"
using namespace std;


Card::Card() {
    id = -1;            // set id = -1, this card is an instance of open space on the board
    orientation = 0;
    isden = 0;
    endtrail = 0;   

    top = 'n';         // filler cards do not have true tblr values. Sides = "null".
    bot = 'n';
    left = 'n';
    right = 'n';
/*
    T_R = 'n';
    T_L = 'n';
    B_R = 'n';
    B_L = 'n';
    mid = 'n';
*/
}

Card::Card(int inputid) {
    id = inputid;           // set this cards id
    assignSides(id);        // set default sides corresponding to this card type
    isfiller = false;		// Card initialized with id is a real card
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


// Kurt -probably going to have to change this if he doesn't give us a list of cards
// Great for right now though, let's keep it
void Card::assignSides(int id) {
    
    // mark top of card depending on card id
    if(id == 17 || id == 2 || id == 1 || 
    	id == 23 || id == 10 || id == 13) {          				// card with jungle top
        top = 'j';
    }
    else if (id == 7 || id == 16) {                  				// card with game-trail top
        top = 'g';
    }
    else {                                           				// card with lake top
        top = 'l';
    }
    
    // mark right of card depending on card id
    if(id == 18 || id == 5 || id == 19 
    	|| id == 9 || id == 20 || id == 1 || id == 23) {        	// card with lake right
        right = 'l';
    }

    else if (id == 15 || id == 22 || id == 14 || id == 0 
                || id == 3 || id == 13 || id == 16) {               // card with game-trail right
        right = 'g';

    }
    else {                                                          // card with jungle right
        right = 'j';
    }
    
    // mark bot of card depending on card id
    if(id == 18 || id == 6) {                                       // card with lake bot
        bot = 'l';
    }
    else if (id == 17 || id == 5 || id == 19 || id == 12 || id == 21 || id == 1
             || id == 23 || id == 4 || id == 8 || id == 3) {        // card with jungle bot
        bot = 'j';
    }
    else {                                                          // card with game-trail bot
        bot = 'g';
    }
    
    // mark left of card depending on card id
    if(id == 18 || id == 5 || id == 19 || id == 9 
    	|| id == 20 || id == 12 || id == 21 || id == 15 
    	|| id == 22 || id == 1 || id == 23 || id == 4) {          	// card with lake left
        left = 'l';
    }

    else if (id == 11 || id == 0 || id == 3 || id == 10 
    			|| id == 13 || id == 16) {    						// card with game-trail left
        left = 'g';
    }
    else {                                                          // card with jungle left
        left = 'j';
    }
    
/*
    T_R = 'o';
    T_L = 'o';
    B_R = 'o';
    B_L = 'o';
    mid = 'o';
*/
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

/*
char Card::getT_L(){
    return T_L;
}

char Card::getT_R(){
    return T_R;
}

char Card::getMid(){
    return mid;
}

char Card::getB_L(){
    return B_L;
}

char Card::getB_R(){
    return B_R;
}
*/
