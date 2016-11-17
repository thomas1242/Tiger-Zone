#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <string>
#include <stack>
#include "card.h"

#define UNIQUECARDS 24        		// number of unique cards in the deck
#define MAXCARDS    71        		// max number of cards allowed in the deck
using namespace std;

// Kurt - This whole thing needs a rework to take into account that we will see every card at start.
// Dave said he doesn't know how big deck will be, or how many of each card it has. we would need to make it open ended


class Deck {
    
    public:
        Deck();							// Deck constructor
        ~Deck();
        string getDeckString();			// return string with num cards left in deck (for the GUI)
        int drawCard();                 // pop old card off the deck, return new top card's id, increment count id
        void printDeck();				// for debugging:print count of each card currently in the deck
        int getSize();
        bool isEmpty();                 // return # of cards in the deck (??? Kurt - do you want int?)
    
    private:
        int numCardsInDeck;			    // total nubmer of cards currently in the deck
        int counts[UNIQUECARDS];	    // count of each card currently in the deck
        stack< int > deck;              // stack of card ids
        
};

#endif /* deck_h */
