#include <iostream>
#include "card.h"
#include <string>
using namespace std;


Card::Card() {
    id = -1;            // set id = -1, this card is an instance of open space on the board
    orientation = 0;
    assignSides();        // add edges to this card
    assignCardID();
    tigerVector = 0;
}

Card::Card(int id) {
    this->id = id;          // set this cards id
    assignSides();        // add edges to this card
    assignCardID();
    connectEdgestoCard();
    assignCloseID();
    tigerVector = 0;
    orientation = 0;
}
void Card::rotate() {   // rotate card 90 degrees clockwise
    
//    Edge * temp;
//    temp = rightEdge;
//    rightEdge = botEdge;
//    botEdge = leftEdge;
//    leftEdge = topEdge;
//    topEdge = temp;
    
    
    Edge * temp;
    temp = rightEdge;
    rightEdge = topEdge;
    topEdge = leftEdge;
    leftEdge = botEdge;
    botEdge = temp;
    
    orientation = (orientation + 90) % 360;
    //printCard();
}

void Card::printCard() {
    cout << "Card " << cardID << " with id = " << id << " rotated " << orientation << " degrees." << endl;
    // ---------------------------------
    cout << " "   << " "  << topEdge->getType() << " " << " "   << " " << endl;
    cout << leftEdge->getType()  << " "  << mid << " " << rightEdge->getType() << " " << endl;
    cout << " "   << " "  << botEdge->getType() << " " << " "   << " " << endl;
}

void Card::assignCardID() {
    
    cardID = "";

    if(topEdge->getType() == 'J') {
        cardID += 'J';
    }
    else if(topEdge->getType() == 'L') {
        cardID += 'L';
    }
    else if(topEdge->getType() == 'T') {
        cardID += 'T';
    }
    
    if(rightEdge->getType() == 'J') {
        cardID += 'J';
    }
    else if(rightEdge->getType() == 'L') {
        cardID += 'L';
    }
    else if(rightEdge->getType() == 'T') {
        cardID += 'T';
    }
    
    if(botEdge->getType() == 'J') {
        cardID += 'J';
    }
    else if(botEdge->getType() == 'L') {
        cardID += 'L';
    }
    else if(botEdge->getType() == 'T') {
        cardID += 'T';
    }
    
    if(leftEdge->getType() == 'J') {
        cardID += 'J';
    }
    else if(leftEdge->getType() == 'L') {
        cardID += 'L';
    }
    else if(leftEdge->getType() == 'T') {
        cardID += 'T';
    }
    
    if(id == 1 || id == 2) {
         cardID += 'X';
    }
    else if (id == 15 || id == 22) {
        cardID += 'P';
    }
    else if (id == 17 || id == 24) {
        cardID += 'B';
    }
    else if (id == 19 || id == 26) {
        cardID += 'D';
    }
    else if (id == 27) {
        cardID += 'C';
    }
    else {
        cardID += '-';
    }
}

void Card::assignSides() {    // completable features: lakes (l), game-trails (t), jungle (j), & dens
    
    // mark top of card depending on card id
    if(id == -1) {
        topEdge = new Edge();
    }
    else if(id == 0 || id == 1  || id == 2 || id == 8 || id == 10 || id == 13 || id == 16 || id == 17) {                        // card with lake top
        topEdge = new Edge('J');
    }
    else if (id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 18 || id == 19 || id == 20
             || id == 21  || id == 22 || id == 23 || id == 24 || id == 27) {     // card with trail top13
        topEdge = new Edge('T');
    }
    else {                             // card with jungle top
        topEdge = new Edge('L');
    }
    
    // mark right of card depending on card id
    if(id == -1) {
        rightEdge = new Edge();
    }
    else if(id == 3 || id == 28) {          // card with city right
        rightEdge = new Edge('T');
    }
    else if (id == 0 || id == 1 || id == 2 || id == 4 || id == 5 || id == 6 || id == 12 || id == 25 || id == 26 || id == 11) {                          // card with road right
        rightEdge = new Edge('J');
    }
    else {                                                                                      // card with field right
        rightEdge = new Edge('L');
    }
    
    // mark bot of card depending on card id
    if(id == -1) {
        botEdge = new Edge();
    }
    else if(id == 7 || id == 8 || id == 11 || id == 13 || id == 20 || id == 23 || id == 24 || id == 27 || id == 28) {                                                           // card with city bot
        botEdge = new Edge('L');
    }
    else if (id == 2 || id == 3 || id == 4 || id == 6 || id == 16 || id == 17 || id == 18 || id == 19 || id == 21 || id == 22 || id == 25 || id == 26) {                            // card with field bot
        botEdge = new Edge('T');
    }
    else {                                                                              // card with road bot
        botEdge = new Edge('J');
    }
    
    // mark left of card depending on card id
    if(id == -1) {
        leftEdge = new Edge();
    }
    else if(id == 3 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 21 || id == 22 || id == 23 || id == 24 || id == 28) {          // card with city left
        leftEdge = new Edge('T');
    }
    else if (id == 7 || id == 8 || id == 10 || id == 20 || id == 27) {    // card with road left
        leftEdge = new Edge('L');
    }
    else {                                                                              // card with field left
        leftEdge = new Edge('J');
    }
    
    
    // mark MID of card depending on card id
    if(id == 7 || id == 8 || id == 10 || id == 20) {                        // card with lake top
        mid = 'L';
    }
    else if (id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19
             || id == 21 || id == 22 || id == 25 || id == 26 || id == 23 || id == 24 || id == 28) {     // card with trail top13
        mid = 'T';
    }
    else if (id == 0 || id == 10 || id == 11 || id == 12 || id == 13) {     // card with trail top13
        mid = 'J';
    }
    else {                             // card with jungle top
        mid = 'o';
    }
    
    
}


string Card::getCardID() {
    return cardID;
}

char Card::getTop() {
    return topEdge->getType();
}

char Card::getBot() {
    return botEdge->getType();
}

char Card::getRight() {
    return rightEdge->getType();
}

char Card::getLeft() {
    return leftEdge->getType();
}

int Card::getId() {
    return id;
}

int Card::getOrient() {
    return orientation;
}

char Card::getMid(){
    return mid;
}

void Card::connectEdgestoCard() {
    //======== add jungle/lake/trail region to this card
    
    // add jungle region to this card
    if( id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27 || id == 28) {
        j1 = new Jungle();
    }
    if(id == 3 || id == 4 || id == 5 || id == 6 || id == 10 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27 || id == 28) {
        j2 = new Jungle();
    }
    if(id == 3 || id == 6 || id == 21 || id == 22) {
        j3 = new Jungle();
    }
    if(id == 3) {
        j4 = new Jungle();
    }
    // add lake region to this card
    if(id == 7 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27 || id == 28) {
        l1 = new Lake();
    }
    if(id == 11 || id == 13 || id == 28) {
        l2 = new Lake();
    }
    // add trail region to this card
    if(id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27 || id == 28) {
        t1 = new Trail();
    }
    if(id == 3 || id == 6 || id == 21 || id == 22) {
        t2 = new Trail();
    }
    if(id == 3 || id == 6 || id == 21 || id == 22) {
        t3 = new Trail();
    }
    if(id == 3) {
        t4 = new Trail();
    }
    
    // connect edges to card's jungle/lake/trail region(s)
    // depending on the card, edges connect to different regions
    
    // 'J' edge has one Jungle pointer
    
    // 'L' edge has one Lake pointer
    
    // 'T' edge has one Trail and two Jungle pointers
    //------------------------------------------------------------------
    
    // connect top edge to card's internal regions
    
    reConnect();
}

void Card::reConnect() {
    
    Edge * curr_topEdge = new Edge();   // where the default edges are located
    Edge * curr_rightEdge = new Edge();
    Edge * curr_botEdge = new Edge();
    Edge * curr_leftEdge = new Edge();

    
    if(orientation == 0) {
        curr_topEdge   = topEdge;
        curr_rightEdge = rightEdge;
        curr_botEdge   = botEdge;
        curr_leftEdge  = leftEdge;
    }
    else if (orientation == 90) {
        curr_topEdge   = rightEdge;
        curr_rightEdge = botEdge;
        curr_botEdge   = leftEdge;
        curr_leftEdge  = topEdge;
    }
    else if (orientation == 180) {
        curr_topEdge   = botEdge;
        curr_rightEdge = leftEdge;
        curr_botEdge   = topEdge;
        curr_leftEdge  = rightEdge;
    }
    else if (orientation == 270) {
        curr_topEdge   = leftEdge;
        curr_rightEdge = topEdge;
        curr_botEdge   = rightEdge;
        curr_leftEdge  = botEdge;
    }
    
    // connect top edge to card's internal regions
    if(id == 0) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->j1 = j1;
        curr_botEdge->j1 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 1) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->j1 = j1;
        curr_botEdge->j1 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 2) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->j1 = j1;
        curr_botEdge->t1 = t1;
        curr_botEdge->j1 = j1;
        curr_botEdge->j2 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 3) {
        
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t4;
        curr_topEdge->j2 = j3;
        
        curr_rightEdge->j1 = j3;
        curr_rightEdge->t1 = t3;
        curr_rightEdge->j2 = j4;
        
        curr_botEdge->j1 = j4;
        curr_botEdge->t1 = t2;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
        
    }
    else if(id == 4) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->j1 = j2;
        
        curr_botEdge->j1 = j2;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j1;
        
        curr_leftEdge->j1 = j1;
    }
    else if(id == 5) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->j1 = j2;
        
        curr_botEdge->j1 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 6) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t3;
        curr_topEdge->j2 = j3;
        
        curr_rightEdge->j1 = j3;
        
        curr_botEdge->j1 = j3;
        curr_botEdge->t1 = t2;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 7) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->l1 = l1;
        curr_botEdge->l1 = l1;
        curr_leftEdge->l1 = l1;
    }
    else if(id == 8) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->l1 = l1;
        curr_botEdge->l1 = l1;
        curr_leftEdge->l1 = l1;
    }
    else if(id == 9) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->l1 = l1;
        curr_botEdge->j1 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 10) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->l1 = l1;
        curr_botEdge->j1 = j2;
        curr_leftEdge->l1 = l1;
    }
    else if(id == 11) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->j1 = j1;
        curr_botEdge->l1 = l2;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 12) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->j1 = j1;
        curr_botEdge->j1 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 13) {
        curr_topEdge->j1 = j1;
        curr_rightEdge->l1 = l2;
        curr_botEdge->l1 = l1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 14) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 15) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 16) {
        curr_topEdge->j1 = j1;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j1;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 17) {
        curr_topEdge->j1 = j1;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j1;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 18) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j2;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j1;
        
        curr_leftEdge->j1 = j1;
    }
    else if(id == 19) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j2;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j1;
        
        curr_leftEdge->j1 = j1;
    }
    else if(id == 20) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        curr_rightEdge->l1 = l1;
        curr_botEdge->l1 = l1;
        curr_leftEdge->l1 = l1;
        
    }
    else if(id == 21) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t3;
        curr_topEdge->j2 = j3;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j3;
        curr_botEdge->t1 = t2;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 22) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t3;
        curr_topEdge->j2 = j3;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->j1 = j3;
        curr_botEdge->t1 = t2;
        curr_botEdge->j2 = j2;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 23) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->l1 = l1;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 24) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        
        curr_rightEdge->l1 = l1;
        
        curr_botEdge->l1 = l1;
        
        curr_leftEdge->j1 = j2;
        curr_leftEdge->t1 = t1;
        curr_leftEdge->j2 = j1;
    }
    else if(id == 25) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->j1 = j2;
        curr_botEdge->j1 = j2;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 26) {
        curr_topEdge->l1 = l1;
        curr_rightEdge->j1 = j2;
        curr_botEdge->j1 = j2;
        curr_botEdge->t1 = t1;
        curr_botEdge->j2 = j1;
        curr_leftEdge->j1 = j1;
    }
    else if(id == 27) {
        curr_topEdge->j1 = j1;
        curr_topEdge->t1 = t1;
        curr_topEdge->j2 = j2;
        curr_rightEdge->l1 = l1;
        curr_botEdge->l1 = l1;
        curr_leftEdge->l1 = l1;
    }
    else if(id == 28) {
        curr_topEdge->l1 = l1;          // connect top lake edge's l1 pointer to lake 1 region
        
        curr_rightEdge->j1 = j1;        // connect right trail edge's j1 pointer to jungle 1 region
        curr_rightEdge->t1 = t1;        // connect right trail edge's t1 pointer to trail  1 region
        curr_rightEdge->j2 = j2;        // connect right trail edge's j2 pointer to jungle 2 region
        
        curr_botEdge->l1 = l2;          // connect bot lake edge's l1 pointer to lake 2 region in card
        
        curr_leftEdge->j1 = j2;         // connect left trail edge's j1 pointer to jungle 2 region
        curr_leftEdge->t1 = t1;         // connect left trail edge's t1 pointer to trail  1 region
        curr_leftEdge->j2 = j1;         // connect left trail edge's j2 pointer to jungle 1 region
    }
    
}


void Card::assignCloseID() {
    
     // 0 if extending trail, 1 if extending lake, 2 if closing trail, 3 if closing lake, -1 non of the above
    
    if( id == 4 || id == 5 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 23 || id == 24 ) {              // extending trail
        extendID = 0;
    }
    else if( id == 2 || id == 3 || id == 6 || id == 20 || id == 21 || id == 22 || id == 25 || id == 26 || id == 27  ) {        // closing trail
        extendID = 2;
    }
    else if( id == 7 || id == 8 || id == 9 || id == 10 || id == 20 || id == 23 || id == 24 || id == 27  ) {        // extending lake
        extendID = 1;
    }
    else if( id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 21 || id == 22 || id == 25 || id == 26 || id == 28) {        // card that closes a lake off
        extendID = 3;
    }
    else {
        extendID = -1;
    }
    
    
}

// print valid meeple locations on the current card
void Card::assignZones(int & L1, int & L2, int & J1, int & J2, int & J3, int & J4, int & T1, int & T2, int & T3, int & T4) {
    
    // top edge
    if( topEdge->getType() == 'J' ) {
        if(topEdge->j1 == j1) {
            setValue( J1 , 1);
        }
        if(topEdge->j1 == j2) {
            setValue( J2 , 1);
        }
        if(topEdge->j1 == j3) {
            setValue( J3 , 1);
        }
        if(topEdge->j1 == j4) {
            setValue( J4 , 1);
        }
    }
    if( topEdge->getType() == 'L' ) {
        
        if( leftEdge->getType() != 'L' && rightEdge->getType() != 'L' ) { // left and right edge not lake
            if(topEdge->l1 == l1) {
                setValue( L1 , 2);
            }
            if(topEdge->l1 == l2) {
                setValue( L2 , 2);
            }
        }
        else if( leftEdge->getType() != 'L' ) {    // left edge not lake
            if(topEdge->l1 == l1) {
                setValue( L1 , 2);
            }
            if(topEdge->l1 == l2) {
                setValue( L2 , 2);
            }
        }
        else {                                          // right edge not lake
            if(topEdge->l1 == l1 && id != 13) {
                setValue( L1 , 1);
            }
            if(topEdge->l1 == l2 && id != 13) {
                setValue( L2 , 1);
            }
        }
        
    }
    if( topEdge->getType() == 'T' ) {
        if(topEdge->j1 == j1) {
            setValue( J1 , 1);
        }
        if(topEdge->j1 == j2) {
            setValue( J2 , 1);
        }
        if(topEdge->j1 == j3) {
            setValue( J3 , 1);
        }
        if(topEdge->j1 == j4) {
            setValue( J4 , 1);
        }
        
        if(topEdge->t1 == t1) {
            setValue( T1 , 2);
        }
        if(topEdge->t1 == t2) {
            setValue( T2 , 2);
        }
        if(topEdge->t1 == t3) {
            setValue( T3 , 2);
        }
        if(topEdge->t1 == t4) {
            setValue( T4 , 2);
        }
        if(topEdge->j2 == j1) {
            setValue( J1 , 3);
        }
        if(topEdge->j2 == j2) {
            setValue( J2 , 3);
        }
        if(topEdge->j2 == j3) {
            setValue( J3 , 3);
        }
        if(topEdge->j2 == j4) {
            setValue( J4 , 3);
        }
    }
    
    // left edge
    if( leftEdge->getType() == 'J' ) {
        if(leftEdge->j1 == j1) {
            setValue( J1 , 1);
        }
        if(leftEdge->j1 == j2) {
            setValue( J2 , 1);
        }
        if(leftEdge->j1 == j3) {
            setValue( J3 , 1);
        }
        if(leftEdge->j1 == j4) {
            setValue( J4 , 1);
        }
    }
    if( leftEdge->getType() == 'L' ) {
        
        if( topEdge->getType() != 'L' && botEdge->getType() != 'L' ) { // top and bot edge not lake
            if(leftEdge->l1 == l1) {
                setValue( L1 , 4);
            }
            if(leftEdge->l1 == l2) {
                setValue( L2 , 4);
            }
        }
        else if( topEdge->getType() != 'L' ) {    // top edge not lake
            if(leftEdge->l1 == l1) {
                setValue( L1 , 4);
            }
            if(leftEdge->l1 == l2) {
                setValue( L2 , 4);
            }
        }
        else {                                          // right edge not lake
            if(leftEdge->l1 == l1 && id != 13) {
                setValue( L1 , 1);
            }
            if(leftEdge->l1 == l2 && id != 13) {
                setValue( L2 , 1);
            }
        }
        
        
        
    }
    if( leftEdge->getType() == 'T' ) {
        if(leftEdge->j2 == j1) {
            setValue( J1 , 1);
        }
        if(leftEdge->j2 == j2) {
            setValue( J2 , 1);
        }
        if(leftEdge->j2 == j3) {
            setValue( J3 , 1);
        }
        if(leftEdge->j2 == j4) {
            setValue( J4 , 1);
        }
        
        if(leftEdge->t1 == t1) {
            setValue( T1 , 4);
        }
        if(leftEdge->t1 == t2) {
            setValue( T2 , 4);
        }
        if(leftEdge->t1 == t3) {
            setValue( T3 , 4);
        }
        if(leftEdge->t1 == t4) {
            setValue( T4 , 4);
        }
        
        if(leftEdge->j1 == j1) {
            setValue( J1, 7 );
        }
        if(leftEdge->j1 == j2) {
            setValue( J2, 7 );
        }
        if(leftEdge->j1 == j3) {
            setValue( J3, 7 );
        }
        if(leftEdge->j1 == j4) {
            setValue( J4, 7 );
        }
    }
    
    // right edge
    if( rightEdge->getType() == 'J' ) {
        if(rightEdge->j1 == j1) {
            setValue( J1, 3 );
        }
        if(rightEdge->j1 == j2) {
            setValue( J2, 3 );
        }
        if(rightEdge->j1 == j3) {
            setValue( J3, 3 );
        }
        if(rightEdge->j1 == j4) {
            setValue( J4, 3 );
        }
    }
    if( rightEdge->getType() == 'L' ) {
        
        if( topEdge->getType() != 'L' && botEdge->getType() != 'L' ) { // top and bot edge not lake
            if(rightEdge->l1 == l1) {
                setValue( L1 , 6);
            }
            if(rightEdge->l1 == l2) {
                setValue( L2 , 6);
            }
        }
        else if( topEdge->getType() != 'L' ) {    // top edge not lake
            if(rightEdge->l1 == l1) {
                setValue( L1 , 6);
            }
            if(rightEdge->l1 == l2) {
                setValue( L2 , 6);
            }
        }
        else {                                          // right edge not lake
            if(rightEdge->l1 == l1) {
                setValue( L1 , 3);
            }
            if(rightEdge->l1 == l2) {
                setValue( L2 , 3);
            }
        }
        
    }
    if( rightEdge->getType() == 'T' ) {
        if(rightEdge->j2 == j1) {
            setValue( J1, 9 );
        }
        if(rightEdge->j2 == j2) {
            setValue( J2, 9 );
        }
        if(rightEdge->j2 == j3) {
            setValue( J3, 9 );
        }
        if(rightEdge->j2 == j4) {
            setValue( J4, 9 );
        }
        
        if(rightEdge->t1 == t1) {
            setValue( T1, 6 );
        }
        if(rightEdge->t1 == t2) {
            setValue( T2, 6 );
        }
        if(rightEdge->t1 == t3) {
            setValue( T3, 6 );
        }
        if(rightEdge->t1 == t4) {
            setValue( T4, 6 );
        }
        
        if(rightEdge->j1 == j1) {
            setValue( J1, 3 );
        }
        if(rightEdge->j1 == j2) {
            setValue( J2, 3 );
        }
        if(rightEdge->j1 == j3) {
            setValue( J3, 3 );
        }
        if(rightEdge->j1 == j4) {
            setValue( J4, 3 );
        }
    }
    
    // bot edge
    if( botEdge->getType() == 'J' ) {
        if(botEdge->j1 == j1) {
            setValue( J1, 7 );
        }
        if(botEdge->j1 == j2) {
            setValue( J2, 7 );
        }
        if(botEdge->j1 == j3) {
            setValue( J3, 7 );
        }
        if(botEdge->j1 == j4) {
            setValue( J4, 7 );
        }
    }
    if( botEdge->getType() == 'L' ) {
        
        if( leftEdge->getType() != 'L' && rightEdge->getType() != 'L' ) { // left and right edge not lake
            if(botEdge->l1 == l1) {
                setValue( L1 , 8);
            }
            if(botEdge->l1 == l2) {
                setValue( L2 , 8);
            }
        }
        else if( leftEdge->getType() != 'L' ) {    // left edge not lake
            if(botEdge->l1 == l1) {
                setValue( L1 , 8);
            }
            if(botEdge->l1 == l2) {
                setValue( L2 , 8);
            }
        }
        else {                                          // right edge not lake
            if(botEdge->l1 == l1 && id != 13) {
                setValue( L1 , 7);
            }
            if(botEdge->l1 == l2 && id != 13) {
                setValue( L2 , 7);
            }
        }
        
    }
    if( botEdge->getType() == 'T' ) {
        if(botEdge->j2 == j1) {
            setValue( J1, 7 );
        }
        if(botEdge->j2 == j2) {
            setValue( J2, 7 );
        }
        if(botEdge->j2 == j3) {
            setValue( J3, 7 );
        }
        if(botEdge->j2 == j4) {
            setValue( J4, 7 );
        }
        
        if(botEdge->t1 == t1) {
            setValue( T1, 8 );
        }
        if(botEdge->t1 == t2) {
            setValue( T2, 8 );
        }
        if(botEdge->t1 == t3) {
            setValue( T3, 8 );
        }
        if(botEdge->t1 == t4) {
            setValue( T4, 8 );
        }
        
        if(botEdge->j1 == j1) {
            setValue( J1, 9 );
        }
        if(botEdge->j1 == j2) {
            setValue( J2, 9 );
        }
        if(botEdge->j1 == j3) {
            setValue( J3, 9 );
        }
        if(botEdge->j1 == j4) {
            setValue( J4, 9 );
        }
        
        
        
    }
    
    if(      j1 != NULL && j1->getOwner() != -1 ) {
        J1 = 10;
    }
    else if( j2 != NULL && j2->getOwner() != -1 ) {
        J2 = 10;
    }
    else if( j3 != NULL && j3->getOwner() != -1 ) {
        J3 = 10;
    }
    else if( j4 != NULL && j4->getOwner() != -1 ) {
        J4 = 10;
    }
    
    if(      t1 != NULL && t1->getOwner() != -1 ) {
        T1 = 10;
    }
    else if( t2 != NULL && t2->getOwner() != -1 ) {
        T2 = 10;
    }
    else if( t3 != NULL && t3->getOwner() != -1 ) {
        T3 = 10;
    }
    else if( t4 != NULL && t4->getOwner() != -1 ) {
        T4 = 10;
    }
    
    if(      l1 != NULL && l1->getOwner() != -1 ) {
        L1 = 10;
    }
    else if( l2 != NULL && l2->getOwner() != -1 ) {
        L2 = 10;
    }
    if( id == 13 && orientation == 0) {
        hardSet( J1, 1 );
        hardSet( L1, 8 );
        hardSet( L2, 6 );
    }
    if( id == 13 && orientation == 90) {
        hardSet( J1, 1 );
        hardSet( L1, 6 );
        hardSet( L2, 2 );
    }
    if( id == 13 && orientation == 180) {
        hardSet( J1, 1 );
        hardSet( L1, 2 );
        hardSet( L2, 4 );
    }
    if( id == 13 && orientation == 270) {
        hardSet( J1, 1 );
        hardSet( L1, 4 );
        hardSet( L2, 8 );
    }
    
    if( (id == 5 || id == 14 || id == 15 || id == 23 || id == 24) && orientation == 180) {
        setValue( T1, 5 );
    }
    if( (id == 16 || id == 17) && orientation == 90) {
        setValue( T1, 5 );
    }
    
    /* when specifying where a tiger is to be placed on a tile, specify the smallest
       zone number that describes the feature into which it is being added.       */
    
//    cout << "Card " << getCardID() << " with orientation " << getOrient() << endl;
//    if(L1 != 10) {
//        cout << "L1 in zone: " << L1 << endl;
//    }
//    if(L2 != 10) {
//        cout << "L2 in zone: " << L2 << endl;
//    }
//    if(J1 != 10) {
//        cout << "J1 in zone: " << J1 << endl;
//    }
//    if(J2 != 10) {
//        cout << "J2 in zone: " << J2 << endl;
//    }
//    if(J3 != 10) {
//        cout << "J3 in zone: " << J3 << endl;
//    }
//    if(J4 != 10) {
//        cout << "J4 in zone: " << J4 << endl;
//    }
//    if(T1 != 10) {
//        cout << "T1 in zone: " << T1 << endl;
//    }
//    if(T2 != 10) {
//        cout << "T2 in zone: " << T2 << endl;
//    }
//    if(T3 != 10) {
//        cout << "T3 in zone: " << T3 << endl;
//    }
//    if(T4 != 10) {
//        cout << "T4 in zone: " << T4 << endl;
//    }
}

void Card::setValue( int & oldVal, int newVal  ) {
    if( newVal < oldVal) {
        oldVal = newVal;
    }
}

void Card::hardSet(  int & oldVal, int newVal  ) {
     oldVal = newVal;
}

int Card::getTigerLocs() {
    return tigerVector;
}

void Card::addTiger(int zone) {
    tigerVector = tigerVector | (1 << zone);
}

