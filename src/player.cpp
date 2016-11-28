#include "player.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b, Deck * d) {
    theBoard = b;           // point this players to the game's board;
    theDeck = d;            // point this players to the game's deck
    score = 0;
    meeplesAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
    hasCard = false;
}

void Player::takeCard() {
    currCard = theDeck->drawCard();                  // draw new card id from the deck
    currCard->printCard();
    theBoard->refreshPossibleMoves();
    theBoard->updatePossibleMoves(currCard);
    
    if(!(theBoard->possibleMoves.empty())) {
        hasCard = true;
    }
    cout << endl << "Has Card: " << hasCard << endl;
   // theBoard->printBoard();
 //   currCard->printCard();
}

bool Player::takeTurn(int i, int j, int orientation) {
    bool res = false;

    for (list<Moves*>::iterator iter = theBoard->possibleMoves.begin(); iter != theBoard->possibleMoves.end(); ++iter) {
        if((*iter)->icoord == i && (*iter)->jcoord == j) {
            if( orientation == 0 && (*iter)->possibleorientations[0] == 1) {
                theBoard->placeCard(i, j, currCard, 0);
                res = true;
                hasCard = true;
            }
            else if( orientation == 90 && (*iter)->possibleorientations[1] == 1) {
                theBoard->placeCard(i, j, currCard, 1);
                res = true;
                hasCard = true;
            }
            else if( orientation == 180 && (*iter)->possibleorientations[2] == 1) {
                theBoard->placeCard(i, j, currCard, 2);
                res = true;
                hasCard = true;
            }
            else if( orientation == 270 && (*iter)->possibleorientations[3] == 1) {
                theBoard->placeCard(i, j, currCard, 3);
                res = true;
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

int Player::getMeeples() {
    return meeplesAvailable;
}

// for gui
Card * Player::getCard() {
    return currCard;
}
