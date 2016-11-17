#include "player.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include <iostream>
#include <unistd.h>

<<<<<<< HEAD
Player::Player(Board board, Deck deck) {
    
    score = 0;              
    meeplesAvailable = 7;   // players start with 7 meeples
    
    theBoard = board;
    theDeck = deck;
=======
Player::Player(Board * b) {
    theBoard = b;            // point this players theDeck pointer to the board's deck
    score = 0;              
    meeplesAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
    hasCard = false;
>>>>>>> sfmlBranch
}

void Player::drawCard() {
    
<<<<<<< HEAD
    cout << "# cards in deck: " << theBoard->getDeck()->getSize();      // print current card to be played
    Card * new_card = new Card( theBoard->getDeck()->drawCard() );		// draw new card id from the deck
    //theBoard->updatePossibleMoves( new_card );                          // update possible moves
    cout << " --> draw card: " << new_card->getId() << endl;            // print current card to be played
=======
    currCard = new Card( theBoard->getDeck()->drawCard() );      // draw new card id from the deck
    theBoard->updatePossibleMoves( currCard );                          // update possible moves
>>>>>>> sfmlBranch
    
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
