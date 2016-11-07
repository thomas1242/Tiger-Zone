#include "main.h"
#ifndef Deck_h
#define Deck_h
#include <string>

class Deck {

public:
	int cards_in_deck = 0;			// cards currently in the deck
	
	// array to hold count of each card in the deck
	int counts[uniquecards];
	
	// HARDCODED VALUES FOR CARCASSONNE ONLY. EDIT IF CARDS CHANGE
	// 24 unique cards at indices 1-24, fixed number of each, 72 cards total.    
	int maxCounts[] = { 0, 3, 1, 2, 3, 2, 3, 3, 8, 5, 1, 9, 3, 3, 4, 3, 3, 1, 4, 1, 1, 2, 2, 2, 2};

	static inline string int2Str(int x);
	void popCardOffDeck();
	std::string getDeckString();

private:


};

#endif