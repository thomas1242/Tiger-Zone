#include <stdlib.h>     /* srand, rand */
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include "deck.h"
#include "card.h"
using namespace std;


// Kurt - This whole thing needs a rework to take into account that we will see every card at start.
// Dave said he doesn't know how big deck will be, or how many of each card it has. we would need to make it open ended


// Deck constructor
Deck::Deck() {
    
    numCardsInDeck = 0;    					
    for(int i = 0; i < UNIQUECARDS; i++) {	 	// initally 0 cards in the deck
        counts[i] = 0;
    }

    int maxCounts[] = { 3, 1, 2, 3, 2, 3, 3, 8, 5, 1, 9, 3, 3, 4, 3, 3, 1, 4, 1, 2, 2, 2, 2, 2 };
    srand (time(NULL));
    int id;

    for(int i = 0; i < MAXCARDS; i++) {   // put 71 cards into the deck
        do{
            id = rand() % 24;                                // generate random card
        } while ( counts[id] >= maxCounts[id] );       // only use cards we need
        
        deck.push( new Card(id) );	// put the card in the deck
        counts[id]++;
        numCardsInDeck++;
    }
    deck.push( new Card(3) );         // push center card on top of the deck
    numCardsInDeck++;
}

// pop old top card off the deck, return new top card's id to the player who drew the card
Card* Deck::drawCard() {
    
    numCardsInDeck--;

    if(isEmpty()) {
        cout << "empty" << endl;
        return NULL;
    }
    
    Card * top = deck.top();       // id of new top card (the card to be placed)
    deck.pop();

    cout << "card " << top->getId() << " drawn from the deck, " << numCardsInDeck <<" cards left." << endl;
    return top;                 // return id of top card
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


