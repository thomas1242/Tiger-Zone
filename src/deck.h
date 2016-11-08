#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <string>
#include <stack>
#define UNIQUECARDS 24        		// number of unique cards in the deck
#define MAXCARDS    71        		// max number of cards allowed in the deck
using namespace std;

class Deck {
    
    public:
        Deck();							// Deck constructor
        ~Deck();
        string getDeckString();			// return string with num cards left in deck (for the GUI)
        void popCardOffDeck();			// pop top card off the deck
        void printDeck();				// for debugging:print count of each card currently in the deck
        
    private:
        int numCardsInDeck;			    // total nubmer of cards currently in the deck
        int counts[UNIQUECARDS];	    // count of each card currently in the deck
        stack< int > deck;              // stack of card ids
        
};

#endif /* deck_h */
