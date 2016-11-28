#include "player.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <unistd.h>

Player::Player(Board * b, Deck * d, int pid) {
    theBoard = b;           // point this players to the game's board;
    theDeck = d;            // point this players to the game's deck
    score = 0;
    meeplesAvailable = 7;   // players start with 7 meeples
    currCard = NULL;
    hasCard = false;
    playerID = pid;
}

void Player::takeCard() {
    
    currCard = theDeck->drawCard();                  // draw new card id from the deck
    theBoard->updatePossibleMoves( currCard );

//    for(int i = 0; i < ROWS; i++) {
//        for(int j = 0; j < COLS; j++) {
//            int n = 1;
//            while(n <= 4) {                          // 0, 90, 180, 270
//                if(theBoard->checkIfFits(i, j, currCard)) {
//                    break;
//                }
//                currCard->rotate();
//                n++;
//            }
//            if( n <= 4) {
//                // update AI current move
//                i = ROWS;
//                j = COLS;
//            }
//        }
//    }

    
    while(theBoard->isPossibleMove() == false ) {
        cout << "Cannot place card " << currCard->getId() << ". Discarded." << endl;
        delete currCard;                                // Card is discarded
        currCard = theDeck->drawCard();                 // draw new card id from the deck
        theBoard->updatePossibleMoves( currCard );
        // TELL SERVER CARD IS DISCARDED, NEW CARD IS DRAWN.
    }
    
    hasCard = true;
    //theBoard->printBoard();
 //   currCard->printCard();
}

bool Player::takeTurn(int i, int j) {
    bool res = false;
    if( theBoard->checkPossibleMove(i, j) ) {
        res = theBoard->placeCard(i, j, currCard, playerID, 0);
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
