#include "main.h"
#include "board.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>

void randomseed() {
	srand (time(NULL));             			
	int card;
	for(int i = 0; i < decksize - 1; i++) {   // put 71 cards into the deck
	   
	    do{
	        card = rand() % 23 + 1;                             // generate random card
	    } while ( counts[ card ] >= maxCounts[  card ] );       // only use cards we need
	    
	    deck.push( card );
	    counts[ card ]++;
	    cards_in_deck++;
	}
}

Deck::Deck() {
	// initally 0 of each card
	for(int i = 0; i < uniquecards; i++) {
    	counts[i] = 0;
	}
}

static inline string int2Str(int x) {
    std::stringstream type;
    type << x;
    return type.str();
}

void popCardOffDeck() {                // pop top card off the deck
    if( deck.size() != 0) {
        deck.pop();
        cards_in_deck--;
    }
}

string getDeckString() {
    std::ostringstream oss;
	oss << cards_in_deck;
    string s = "cards left: " + oss.str();
    return s;