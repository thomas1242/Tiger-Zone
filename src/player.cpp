
#include "player.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include <iostream>

Player::Player(Board board, Deck deck) {
    
    score = 0;              
    meeplesAvailable = 7;   // players start with 7 meeples
    
    theBoard = board;
    theDeck = deck;
}

void Player::takeTurn() {
    
    cout << "# cards in deck: " << theBoard->getDeck()->getSize();      // print current card to be played
    Card * new_card = new Card( theBoard->getDeck()->drawCard() );		// draw new card id from the deck
    //theBoard->updatePossibleMoves( new_card );                          // update possible moves
    cout << " --> draw card: " << new_card->getId() << endl;            // print current card to be played
    
     //theBoard->printBoard();                                     // print board/avail moves for this card
}
