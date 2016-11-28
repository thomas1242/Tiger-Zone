#include "player.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b, int pid) {
    theBoard = b;           // point this players to the game's board;
    score = 0;
    tigersAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
    hasCard = false;
    playerID = pid;
}

int Player::ji_to_xy(int input, char id) {
    int output;
    if(id == 'i') {
        output = -input + ROWS;    //ROWS/2
    }
    if(id == 'j') {
        output = input - COLS;     //COLS/2
    }    
    return output;
}

bool Player::underduress() {
    bool res = false;
    // If AI gets stresssed
    // it makes a quick decision.

    int i = theBoard->possibleMoves.front()->icoord;
    int j = theBoard->possibleMoves.front()->jcoord;

    int x = ji_to_xy(j, 'j');
    int y = ji_to_xy(i, 'i');

    cout << "xy: " << x << ' ' << y << endl;
    out.xcoord = x;
    out.ycoord = y;

    if( theBoard->possibleMoves.front()->possibleorientations[0] == 1) {
        theBoard->placeCard(i, j, currCard, 0, playerID, 0);
        out.orientation = 0;
        res = true;
        hasCard = false;
    }
    else if( theBoard->possibleMoves.front()->possibleorientations[1] == 1) {
        theBoard->placeCard(i, j, currCard, 1, playerID, 0);
        out.orientation = 90;
        res = true;
        hasCard = false;
    }
    else if( theBoard->possibleMoves.front()->possibleorientations[2] == 1) {
        theBoard->placeCard(i, j, currCard, 2, playerID, 0);
        out.orientation = 180;
        res = true;
        hasCard = false;
    }
    else if( theBoard->possibleMoves.front()->possibleorientations[3] == 1) {
        theBoard->placeCard(i, j, currCard, 3, playerID, 0);
        out.orientation = 270;
        res = true;
        hasCard = false;
    }
    return res;
}

void Player::takeCard(Card* input, bool DURESS) {
    currCard = input;
    cout << "pass1" << endl;
    currCard->printCard();
    cout << "pass2" << endl;
    theBoard->refreshPossibleMoves();
    cout << "pass3" << endl;
    theBoard->updatePossibleMoves(currCard);
    cout << "pass4" << endl;

    if(!(theBoard->possibleMoves.empty())) {
        hasCard = true;
        if(DURESS == true) {
            underduress();
        }
    }
    else {
        cout << "error1" << endl;
        delete currCard;  
        hasCard = false;
    }
                                  // Card is discarded
    // TELL SERVER CARD IS DISCARDED, NEW THING IS DONE.
    //theBoard->printBoard();
    // currCard->printCard();
}

bool Player::takeTurn(int i, int j, int orientation) {
    bool res = false;
    for (list<Moves*>::iterator iter = theBoard->possibleMoves.begin(); iter != theBoard->possibleMoves.end(); ++iter) {
        if((*iter)->icoord == i && (*iter)->jcoord == j) {
            if( orientation == 0 && (*iter)->possibleorientations[0] == 1) {
                theBoard->placeCard(i, j, currCard, 0, playerID, 0);
                res = true;
                hasCard = false;
            }
            else if( orientation == 90 && (*iter)->possibleorientations[1] == 1) {
                theBoard->placeCard(i, j, currCard, 1, playerID, 0);
                res = true;
                hasCard = false;
            }
            else if( orientation == 180 && (*iter)->possibleorientations[2] == 1) {
                theBoard->placeCard(i, j, currCard, 2, playerID, 0);
                res = true;
                hasCard = false;
            }
            else if( orientation == 270 && (*iter)->possibleorientations[3] == 1) {
                theBoard->placeCard(i, j, currCard, 3, playerID, 0);
                res = true;
                hasCard = false;
            }
        }
    }
    return res;
}

int Player::getCardId() {
    return currCard->getId();
}

void Player::rotateCard() {
    currCard->rotate();                             // rotate card
}

//Card * Player::getCard() {
//    return currCard;
//}

int Player::getScore() {
    return score;
}

int Player::getTigers() {
    return tigersAvailable;
}

// for gui
Card * Player::getCard() {
    return currCard;
}
