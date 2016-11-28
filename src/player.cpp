#include "player.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b) {
    theBoard = b;           // point this players to the game's board;
    score = 0;
    tigersAvailable = 7;   // players start with 7 tigers
    currCard = NULL;
    hasCard = false;
}

void Player::takeCard(Card* input) {
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

bool Player::underduress(int i, int j) {
    bool res = false;
    // This is incomplete with new implementation!
    // This is just taking first move rn.
    if( theBoard->possibleMoves.front()->possibleorientations[0] == 1) {
        theBoard->placeCard(i, j, currCard, 0);
        res = true;
        hasCard = false;
    }
    if( theBoard->possibleMoves.front()->possibleorientations[1] == 1) {
        theBoard->placeCard(i, j, currCard, 1);
        res = true;
        hasCard = false;
    }
    if( theBoard->possibleMoves.front()->possibleorientations[2] == 1) {
        theBoard->placeCard(i, j, currCard, 2);
        res = true;
        hasCard = false;
    }
    if( theBoard->possibleMoves.front()->possibleorientations[3] == 1) {
        theBoard->placeCard(i, j, currCard, 3);
        res = true;
        hasCard = false;
    }
    return res;
}


bool Player::takeTurn(int i, int j, int orientation) {
    bool res = false;
    bool DURESS = true;
    if(DURESS == true) {
        return underduress(i, j);
    }
    for (list<Moves*>::iterator iter = theBoard->possibleMoves.begin(); iter != theBoard->possibleMoves.end(); ++iter) {
        if((*iter)->icoord == i && (*iter)->jcoord == j) {
            if( orientation == 0 && (*iter)->possibleorientations[0] == 1) {
                theBoard->placeCard(i, j, currCard, 0);
                res = true;
                hasCard = false;
            }
            else if( orientation == 90 && (*iter)->possibleorientations[1] == 1) {
                theBoard->placeCard(i, j, currCard, 1);
                res = true;
                hasCard = false;
            }
            else if( orientation == 180 && (*iter)->possibleorientations[2] == 1) {
                theBoard->placeCard(i, j, currCard, 2);
                res = true;
                hasCard = false;
            }
            else if( orientation == 270 && (*iter)->possibleorientations[3] == 1) {
                theBoard->placeCard(i, j, currCard, 3);
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
