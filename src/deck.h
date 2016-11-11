
#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <string>
#include <stack>

#define UNIQUECARDS 24        		// number of unique cards in the deck
#define MAXCARDS   72      // cards randomly put in deck, doesn't include center card
using namespace std;

class Deck {
    
    public:
        Deck();							// Deck constructor
        ~Deck();
        string getDeckString();			// return string with num cards left in deck (for the GUI)
        int drawCard();                 // pop old card off the deck, return new top card's id
        void printDeck();				// for debugging:print count of each card currently in the deck
        int getSize();
        bool isEmpty();                     // return # of cards in the deck
    
    private:
        int numCardsInDeck;			    // total nubmer of cards currently in the deck
        int counts[UNIQUECARDS];	    // count of each card currently in the deck
        stack< int > deck;              // stack of card ids
        
};

#endif /* deck_h */
