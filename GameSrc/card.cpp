#include <iostream>
#include "card.h"
using namespace std;


Card::Card() {
    id = -1;            // set id = -1, this card is an instance of open space on the board
    
    top = 'o';          // this card is free space
    top_L = 'o';
    top_R = 'o';
    
    bot = 'o';
    bot_L = 'o';
    bot_R = 'o';
    
    left = 'o';
    right = 'o';
    mid = 'o';
    orientation = 0;
    
    top_RoadID = -1;    // not part of any feature
    bot_RoadID = -1;
    left_RoadID = -1;
    right_RoadID = -1;
    mid_RoadID = -1;

    
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
    
    temp = top_R;
    top_R = top_L;
    top_L = bot_L;
    bot_L = bot_R;
    bot_R = temp;
    
    orientation = (orientation + 90) % 360;
    printCard();
}

void Card::printCard() {
    cout << "Card id = " << id << endl;
    // ---------------------------------
    cout << top_L << " "  << top << " " << top_R << " " << endl;
    cout << left  << " "  << mid << " " << right << " " << endl;
    cout << bot_L << " "  << bot << " " << bot_R << " " << endl;
}

void Card::assignSides(int id) {    // completable features: lakes (l), game-trails (t), jungle (j), & dens
    
    // mark top of card depending on card id
    if(id == 0 || id == 1  || id == 2 || id == 8 || id == 10 || id == 13 || id == 16 || id == 17) {                        // card with lake top
        top = 'J';
    }
    else if (id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 18 || id == 19 || id == 20
              || id == 21  || id == 22 || id == 23 || id == 24) {     // card with trail top13
        top = 'T';
    }
    else {                             // card with jungle top
        top = 'L';
    }
    
    // mark right of card depending on card id
    if(id == 3) {          // card with city right
        right = 'T';
    }
    else if (id == 0 || id == 1 || id == 2 || id == 4 || id == 5 || id == 6 || id == 12 || id == 25 || id == 26 || id == 11) {                          // card with road right
        right = 'J';
    }
    else {                                                                                      // card with field right
        right = 'L';
    }
    
    // mark bot of card depending on card id
    if(id == 7 || id == 8 || id == 11 || id == 13 || id == 20 || id == 23 || id == 24 ) {                                                           // card with city bot
        bot = 'L';
    }
    else if (id == 2 || id == 3 || id == 4 || id == 6 || id == 16 || id == 17 || id == 18 || id == 19 || id == 21 || id == 22 || id == 25 || id == 26) {                            // card with field bot
        bot = 'T';
    }
    else {                                                                              // card with road bot
        bot = 'J';
    }
    
    // mark left of card depending on card id
    if(id == 3 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 21 || id == 22 || id == 23 || id == 24) {          // card with city left
        left = 'T';
    }
    else if (id == 7 || id == 8 || id == 10 || id == 20) {    // card with road left
        left = 'L';
    }
    else {                                                                              // card with field left
        left = 'J';
    }
   
   // mark TOP LEFT of card depending on card id
    if(id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 ||
        id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19
          || id == 21 || id == 22 || id == 23 || id == 24) {                        //
        top_L = 'J';
    }
    else if (id == 7) {     //
        top_L = 'L';
    }
    else if (id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 20 || id == 25 || id == 26) {     // card with lake/jungle edge (Hybrid)
        top_L = 'H';
    }
    else {                             //
        top_L = 'o';
    }
    
    // mark TOP RIGHT of card depending on card id
    if(id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6) {                        // card with lake top
        top_R = 'J';
    }
    else if (id == 7 || id == 9) {     // card with trail top13
        top_R = 'L';
    }
    else if (id == 8 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16
              || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23
              || id == 24 || id == 25 || id == 26) {     // card with lake/jungle edge (Hybrid)
        top_R = 'H';
    }
    else {                             // card with jungle top
        top_R = 'o';
    }
    
    // mark BOT RIGHT of card depending on card id
    if(id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 12  || id == 25
            || id == 26) {                        // card with lake top
        bot_R = 'J';
    }
    else if (id == 7 || id == 8 || id == 20|| id == 23|| id == 24) {     // card with trail top13
        bot_R = 'L';
    }
    else if (id == 9 || id == 10 || id == 11 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18
              || id == 19 || id == 21 || id == 22) {     // card with lake/jungle edge (Hybrid)
        bot_R = 'H';
    }
    else {                             // card with jungle top
        bot_R = 'o';
    }
    
    // mark BOT LEFT of card depending on card id
    if(id == 7 || id == 8 || id == 20) {                        // card with lake top
        bot_L = 'L';
    }
    else if (id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6
             || id == 9 || id == 12 || id == 14|| id == 15|| id == 16|| id == 17|| id == 18|| id == 19
             || id == 21 || id == 22 || id == 25 || id == 26) {     // card with trail top13
        bot_L = 'J';
    }
    else if (id == 10 || id == 11 || id == 13 || id == 23 || id == 24) {     // card with lake/jungle edge (Hybrid)
        bot_L = 'H';
    }
    else {                             // card with jungle top
        bot_L = 'o';
    }
    
    
    // mark MID of card depending on card id
    if(id == 7 || id == 8 || id == 10 || id == 20) {                        // card with lake top
        mid = 'L';
    }
    else if (id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19
             || id == 21 || id == 22 || id == 25 || id == 26 || id == 23 || id == 24) {     // card with trail top13
        mid = 'T';
    }
    else if (id == 0 || id == 10 || id == 11 || id == 12 || id == 13) {     // card with trail top13
        mid = 'J';
    }
    else {                             // card with jungle top
        mid = 'o';
    }
    
    
    top_RoadID =   -1;    // not part of any feature
    bot_RoadID =   -1;
    left_RoadID =  -1;
    right_RoadID = -1;
    mid_RoadID =   -1;
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

char Card::getTop_L(){
    return top_L;
}

char Card::getTop_R(){
    return top_R;
}

char Card::getMid(){
    return mid;
}

char Card::getBot_L(){
    return bot_L;
}

char Card::getBot_R(){
    return bot_R;
}
