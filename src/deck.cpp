#include <stdlib.h>     /* srand, rand */
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include "deck.h"
using namespace std;

// Deck constructor
Deck::Deck() {
    
    numCardsInDeck = 0;
    for(int i = 0; i < UNIQUECARDS; i++) {      // initally 0 cards in the deck
        counts[i] = 0;
    }
    
    int maxCounts[] = { 1, 4, 2, 1, 8, 9, 4, 1, 4, 5, 3, 3, 5, 2, 1, 2, 1, 2, 2, 2, 3, 1, 2, 3, 2, 1, 2};
    //    indices       0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26
    srand (time(NULL));
    int id;
    
    for(int i = 0; i < MAXCARDS; i++) {   // put 71 cards into the deck
        do{
            id = rand() % 27;                                // generate random card
        } while ( counts[id] >= maxCounts[id] );       // only use cards we need
        
        deck.push( new Card(id) );  // put the card in the deck
        counts[id]++;
        numCardsInDeck++;
    }
    deck.push( new Card(18) );         // push center card on top of the deck
    numCardsInDeck++;
    printDeck();
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
    return (deck.size() == 0);
}

int Deck::getSize() {
    return numCardsInDeck;
}


