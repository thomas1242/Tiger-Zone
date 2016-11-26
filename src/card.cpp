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

void Card::edgeclone(Edge* output, Edge* input) {
        output->j1 = input->j1;
        output->j2 = input->j2;
        output->t1 = input->t1;
        output->l1 = input->l1;
        output->type = input->type;
}

void Card::printCard() {
    cout << "Card " << cardID << " with id = " << id << " rotated " << orientation << " degrees." << endl;
    // ---------------------------------
    cout << " "   << " "  << topEdge->type << " " << " "   << " " << endl;
    cout << leftEdge->type  << " "  << mid << " " << rightEdge->type << " " << endl;
    cout << " "   << " "  << botEdge->type << " " << " "   << " " << endl;
}

void Card::rotate() {   // rotate card 90 degrees clockwise
    Edge * temp = new Edge();
    edgeclone(temp, rightEdge);
    edgeclone(rightEdge, topEdge);
    edgeclone(topEdge, leftEdge);
    edgeclone(leftEdge, botEdge);
    edgeclone(botEdge, temp);
    
    orientation = (orientation + 90) % 360;
    printCard();
}

void Card::assignCardID() {
    
    cardID = "";

    if(topEdge->type == 'J') {
        cardID += 'J';
    }
    else if(topEdge->type == 'L') {
        cardID += 'L';
    }
    else if(topEdge->type == 'T') {
        cardID += 'T';
    }
    
    if(rightEdge->type == 'J') {
        cardID += 'J';
    }
    else if(rightEdge->type == 'L') {
        cardID += 'L';
    }
    else if(rightEdge->type == 'T') {
        cardID += 'T';
    }
    
    if(botEdge->type == 'J') {
        cardID += 'J';
    }
    else if(botEdge->type == 'L') {
        cardID += 'L';
    }
    else if(botEdge->type == 'T') {
        cardID += 'T';
    }
    
    if(leftEdge->type == 'J') {
        cardID += 'J';
    }
    else if(leftEdge->type == 'L') {
        cardID += 'L';
    }
    else if(leftEdge->type == 'T') {
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
    return topEdge->type;
}

char Card::getBot() {
    return botEdge->type;
}

char Card::getRight() {
    return rightEdge->type;
}

char Card::getLeft() {
    return leftEdge->type;
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
    if(id == 0) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 1) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 2) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j1 = j1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 3) {
        
        topEdge->j1 = j1;
        topEdge->t1 = t4;
        topEdge->j2 = j3;
        
        rightEdge->j1 = j3;
        rightEdge->t1 = t3;
        rightEdge->j2 = j4;
        
        botEdge->j1 = j4;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
        
    }
    else if(id == 4) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->j1 = j2;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 5) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->j1 = j2;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 6) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->j1 = j3;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 7) {
        topEdge->l1 = l1;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }
    else if(id == 8) {
        topEdge->j1 = j1;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }
    else if(id == 9) {
        topEdge->l1 = l1;
        rightEdge->l1 = l1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 10) {
        topEdge->j1 = j1;
        rightEdge->l1 = l1;
        botEdge->j1 = j2;
        leftEdge->l1 = l1;
    }
    else if(id == 11) {
        topEdge->l1 = l1;
        rightEdge->j1 = j1;
        botEdge->l1 = l2;
        leftEdge->j1 = j1;
    }
    else if(id == 12) {
        topEdge->l1 = l1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 13) {
        topEdge->j1 = j1;
        rightEdge->l1 = l2;
        botEdge->l1 = l1;
        leftEdge->j1 = j1;
    }
    else if(id == 14) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 15) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 16) {
        topEdge->j1 = j1;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 17) {
        topEdge->j1 = j1;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 18) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 19) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 20) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
        
    }
    else if(id == 21) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 22) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 23) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->l1 = l1;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 24) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->l1 = l1;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 25) {
        topEdge->l1 = l1;
        rightEdge->j1 = j2;
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 26) {
        topEdge->l1 = l1;
        rightEdge->j1 = j2;
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 27) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }


}

void Card::reConnect() {
    
    // connect top edge to card's internal regions
    if(id == 0) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 1) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 2) {
        topEdge->j1 = j1;
        rightEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j1 = j1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 3) {
        
        topEdge->j1 = j1;
        topEdge->t1 = t4;
        topEdge->j2 = j3;
        
        rightEdge->j1 = j3;
        rightEdge->t1 = t3;
        rightEdge->j2 = j4;
        
        botEdge->j1 = j4;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
        
    }
    else if(id == 4) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->j1 = j2;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 5) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->j1 = j2;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 6) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->j1 = j3;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 7) {
        topEdge->l1 = l1;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }
    else if(id == 8) {
        topEdge->j1 = j1;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }
    else if(id == 9) {
        topEdge->l1 = l1;
        rightEdge->l1 = l1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 10) {
        topEdge->j1 = j1;
        rightEdge->l1 = l1;
        botEdge->j1 = j2;
        leftEdge->l1 = l1;
    }
    else if(id == 11) {
        topEdge->l1 = l1;
        rightEdge->j1 = j1;
        botEdge->l1 = l2;
        leftEdge->j1 = j1;
    }
    else if(id == 12) {
        topEdge->l1 = l1;
        rightEdge->j1 = j1;
        botEdge->j1 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 13) {
        topEdge->j1 = j1;
        rightEdge->l1 = l2;
        botEdge->l1 = l1;
        leftEdge->j1 = j1;
    }
    else if(id == 14) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 15) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 16) {
        topEdge->j1 = j1;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 17) {
        topEdge->j1 = j1;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j1;
        botEdge->t1 = t1;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 18) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 19) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        
        leftEdge->j1 = j1;
    }
    else if(id == 20) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
        
    }
    else if(id == 21) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 22) {
        topEdge->j1 = j1;
        topEdge->t1 = t3;
        topEdge->j2 = j3;
        
        rightEdge->l1 = l1;
        
        botEdge->j1 = j3;
        botEdge->t1 = t2;
        botEdge->j2 = j2;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 23) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->l1 = l1;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 24) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        
        botEdge->l1 = l1;
        
        leftEdge->j1 = j2;
        leftEdge->t1 = t1;
        leftEdge->j2 = j1;
    }
    else if(id == 25) {
        topEdge->l1 = l1;
        rightEdge->j1 = j2;
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 26) {
        topEdge->l1 = l1;
        rightEdge->j1 = j2;
        botEdge->j1 = j2;
        botEdge->t1 = t1;
        botEdge->j2 = j1;
        leftEdge->j1 = j1;
    }
    else if(id == 27) {
        topEdge->j1 = j1;
        topEdge->t1 = t1;
        topEdge->j2 = j2;
        
        rightEdge->l1 = l1;
        botEdge->l1 = l1;
        leftEdge->l1 = l1;
    }

    
    
}









