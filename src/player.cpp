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
    currCard->printCard();
    theBoard->refreshPossibleMoves();
    theBoard->updatePossibleMoves(currCard);

    if(!(theBoard->possibleMoves.empty())) {
        hasCard = true;
    }
    //delete currCard;                                // Card is discarded
    // TELL SERVER CARD IS DISCARDED, NEW THING IS DONE.
    
    hasCard = true;
    //theBoard->printBoard();
    // currCard->printCard();
}

bool Player::takeTurn(int i, int j, int orientation) {
    bool res = false;
    for (list<Moves*>::iterator iter = theBoard->possibleMoves.begin(); iter != theBoard->possibleMoves.end(); ++iter) {
        if((*iter)->icoord == i && (*iter)->jcoord == j) {
            if( orientation == 0 && (*iter)->possibleorientations[0] == 1) {
                res = theBoard->placeCard(i, j, currCard, 0);
                hasCard = true;
            }
            else if( orientation == 90 && (*iter)->possibleorientations[1] == 1) {
                res = theBoard->placeCard(i, j, currCard, 1);
                hasCard = true;
            }
            else if( orientation == 180 && (*iter)->possibleorientations[2] == 1) {
                res = theBoard->placeCard(i, j, currCard, 2);
                hasCard = true;
            }
            else if( orientation == 270 && (*iter)->possibleorientations[3] == 1) {
                theBoard->placeCard(i, j, currCard, 3);
                hasCard = true;
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
