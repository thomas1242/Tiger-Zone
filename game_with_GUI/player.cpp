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

//string strID, Output *out)
void Player::takeCard() {
    
    //currCard = new Card(convertID(strID));                  // draw new card id from the deck
    currCard = theDeck->drawCard();                  // draw new card id from the deck

    
    theBoard->updatePossibleMoves( currCard );

    if(theBoard->isPossibleMove() == false ) {
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
        res = theBoard->placeCard(i, j, currCard, playerID, 0, true);
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

int Player::convertID(string ID)
{
    if(ID == "JJJJ-"){return 0;}
    if(ID == "JJJJX"){return 1;}
    if(ID == "JJTJX"){return 2;}
    if(ID == "TTTT-"){return 3;}
    if(ID == "TJTJ-"){return 4;}
    if(ID == "TJJT-"){return 5;}
    if(ID == "TJTT-"){return 6;}
    if(ID == "LLLL-"){return 7;}
    if(ID == "JLLL-"){return 8;}
    if(ID == "LLJJ-"){return 9;}
    if(ID == "JLJL-"){return 10;}
    if(ID == "LJLJ-"){return 11;}
    if(ID == "LJJJ-"){return 12;}
    if(ID == "JLLJ-"){return 13;}
    if(ID == "TLJT-"){return 14;}
    if(ID == "TLJTP"){return 15;}
    if(ID == "JLTT-"){return 16;}
    if(ID == "JLTTB"){return 17;}
    if(ID == "TLTJ-"){return 18;}
    if(ID == "TLTJD"){return 19;}
    if(ID == "TLLL-"){return 20;}
    if(ID == "TLTT-"){return 21;}     
    if(ID == "TLTTP"){return 22;}
    if(ID == "TLTT-"){return 23;}
    if(ID == "TLLTB"){return 24;}
    if(ID == "LJTJ-"){return 25;}
    if(ID == "LJTJD"){return 26;}
    if(ID == "TLLLC"){return 27;}
}
