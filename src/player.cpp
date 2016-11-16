#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include "player.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b) {
    theBoard = b;            // point this players theDeck pointer to the board's deck
    score = 0;              
    meeplesAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
    hasCard = false;
}

void Player::drawCard() {
    
    currCard = new Card( theBoard->getDeck()->drawCard() );      // draw new card id from the deck
    theBoard->updatePossibleMoves( currCard );                          // update possible moves
    
    if( theBoard->isPossibleMove() == false ) {
        cout << "Cannot place card " << currCard->getId() << ". Discarded." << endl;
        delete currCard;
        currCard = NULL;
    }
    else {
        hasCard = true;
        theBoard->printBoard();
    }
}

bool Player::takeTurn(int i, int j) {
    bool res = false;
    if( theBoard->checkPossibleMove(i, j) ) {
        res = theBoard->placeCard(i, j, currCard);
        hasCard = false;
    }
    return res;
}

int Player::getCardId() {
    return currCard->getId();
}

void Player::rotateCard() {
    currCard->rotate();                             // rotate card
}

Card * Player::getCard() {
    return currCard;
}

int Player::getScore() {
    return score;
}

int Player::getMeeples() {
    return meeplesAvailable;
}
