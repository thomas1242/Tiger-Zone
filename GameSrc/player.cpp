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
    theBoard->updatePossibleMoves( currCard );
    
    while(theBoard->possibleMoves.empty()) {
        cout << "Cannot place card " << currCard->getId() << ". Discarded." << endl;
        delete currCard;                                // Card is discarded
        currCard = theDeck->drawCard();                 // draw new card id from the deck
        theBoard->updatePossibleMoves( currCard );
        // TELL SERVER CARD IS DISCARDED, NEW CARD IS DRAWN.
    }
    
    hasCard = true;
    theBoard->printBoard();
    currCard->printCard();
}

bool Player::takeTurn(int i, int j) {
    bool res = false;

    // This is incomplete with new implementation!
    // This is just taking first move rn.
    if( theBoard->possibleMoves.begin()->possibleorientations[0] == 1) {
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
