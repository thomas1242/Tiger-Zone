#include <stdlib.h>     /* srand, rand */
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include "deck.h"
using namespace std;

// Deck constructor
Deck::Deck() {
    
    numCardsInDeck = -1;    // -1 beca
    for(int i = 0; i < UNIQUECARDS; i++) {	  // initally 0 cards in the deck
        counts[i] = 0;
    }
    int maxCounts[] = { 3, 1, 2, 3, 2, 3, 3, 8, 5, 1, 9, 3, 3, 4, 3, 3, 1, 4, 1, 1, 2, 2, 2, 2 };
    srand (time(NULL));
    int card;
    for(int i = 0; i < MAXCARDS; i++) {   // put 71 cards into the deck
        do{
            card = rand() % 24;                                // generate random card
        } while ( counts[ card ] >= maxCounts[ card ] );       // only use cards we need
        
        deck.push( card );	// put the card in the deck
        counts[ card ]++;
        numCardsInDeck++;
    }
    deck.push( 3 );         // push center card on top of the deck
    numCardsInDeck++;
}

// pop old top card off the deck, return new top card's id to the player who drew the card
int Deck::drawCard() {
    
    if(deck.size() == 0) {
        numCardsInDeck--;
        cout << "empty" << endl;
        return 1;
    }
    
    
    deck.pop();                 // pop old card off deck
    numCardsInDeck--;
    int top = deck.top();       // id of new top card (the card to be placed)
    return top;                 // return id of top card
    
}

// convert int to string to create score string
string Deck::getDeckString() {
    
    ostringstream oss;
    oss << numCardsInDeck;
    string s = "cards left: " + oss.str();
    return s;
    
}

// print number of each type of card currently in the deck
void Deck::printDeck() {
    
    int sum = 0;
    for(int i = 0; i < UNIQUECARDS; i++) {
        cout << "# of " << i << "'s = " << counts[i] << '.' << endl;
        sum += counts[i];
    }
    cout << "total number of cards in the deck = " << sum << endl;
    cout << "total number of cards in the deck = " << numCardsInDeck << endl;
    
}

bool Deck::isEmpty() {
    return (numCardsInDeck == 0);
}

int Deck::getSize() {
    return numCardsInDeck;
}


