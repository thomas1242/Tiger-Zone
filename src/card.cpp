#include <iostream>
#include "card.h"
#include <string>
using namespace std;


Card::Card() {
    id = -1;            // set id = -1, this card is an instance of open space on the board
    orientation = 0;
    assignSides();        // add edges to this card
    assignCardID();
}

Card::Card(int id) {
    this->id = id;          // set this cards id
    assignSides();        // add edges to this card
    assignCardID();
    
    connectEdgestoCard();
    
    orientation = 0;
}
void Card::edgeclone(Edge* ae, Edge* be) {
        ae->j1 = be->j1;
        ae->j2 = be->j2;
        ae->t1 = be->t1;
        ae->l1 = be->l1;
        ae->type = be->type;
}

void Card::rotate() {   // rotate card 90 degrees clockwise
    cout << "Before edge* creation" << endl;
    Edge * temp = new Edge();
    cout << "After edge* creation" << endl;
    edgeclone(temp, rightEdge);
    edgeclone(rightEdge, topEdge);
    edgeclone(topEdge, leftEdge);
    edgeclone(leftEdge, botEdge);
    edgeclone(botEdge, temp);
    
    orientation = (orientation + 90) % 360;
    printCard();
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
             || id == 21  || id == 22 || id == 23 || id == 24) {     // card with trail top13
        topEdge = new Edge('T');
    }
    else {                             // card with jungle top
        topEdge = new Edge('L');
    }
    
    // mark right of card depending on card id
    if(id == -1) {
        rightEdge = new Edge();
    }
    else if(id == 3) {          // card with city right
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
    else if(id == 7 || id == 8 || id == 11 || id == 13 || id == 20 || id == 23 || id == 24 ) {                                                           // card with city bot
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
    else if(id == 3 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 21 || id == 22 || id == 23 || id == 24) {          // card with city left
        leftEdge = new Edge('T');
    }
    else if (id == 7 || id == 8 || id == 10 || id == 20) {    // card with road left
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
             || id == 21 || id == 22 || id == 25 || id == 26 || id == 23 || id == 24) {     // card with trail top13
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
    if( id == 0 || id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27) {
        j1 = new Jungle();
    }
    if(id == 3 || id == 4 || id == 5 || id == 6 || id == 10 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27) {
        j2 = new Jungle();
    }
    if(id == 3 || id == 6 || id == 21 || id == 22) {
        j3 = new Jungle();
    }
    if(id == 3) {
        j4 = new Jungle();
    }
    // add lake region to this card
    if(id == 7 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27) {
        l1 = new Lake();
    }
    if(id == 11 || id == 13) {
        l2 = new Lake();
    }
    // add trail region to this card
    if(id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20 || id == 21 || id == 22 || id == 23 || id == 24 || id == 25 || id == 26 || id == 27) {
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
    
    

    
}









