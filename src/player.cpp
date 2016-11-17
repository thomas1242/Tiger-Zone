#include "player.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b, Deck * d) {    
    theBoard = b;          	// point this players to the game's board;
    theDeck = d;           	// point this players to the game's deck
    score = 0;              
    meeplesAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
}

void Player::takeCard() {
/*    
    cout << "# cards in deck: " << theDeck->getDeck()->getSize();      // print current card to be played
    //theBoard->updatePossibleMoves( new_card );                          // update possible moves
    cout << " --> draw card: " << new_card->getId() << endl;            // print current card to be played
*/    
    currCard = theDeck->drawCard();      // draw new card id from the deck
    
    while(theBoard->isPossibleMove() == false ) {
        cout << "Cannot place card " << currCard->getId() << ". Discarded." << endl;
        delete currCard;					 // Card is discarded
        currCard = NULL;
        currCard = theDeck->drawCard();      // draw new card id from the deck
        // TELL SERVER CARD IS DISCARDED, NEW CARD IS DRAWN.
    }

    theBoard->printBoard();
}

bool Player::takeTurn(int i, int j) {
    bool res = false;

    //CHANGE, HAS TO CHECK AVAILABLE SIDES
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

//Card * Player::getCard() {
//    return currCard;
//}

int Player::getScore() {
    return score;
}

int Player::getMeeples() {
    return meeplesAvailable;
}
