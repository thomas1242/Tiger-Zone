#include "main.h"
#include "board.h"
#include <stdlib.h>     /* srand, rand */
#include <string>

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


// generate random deck of tiles --------------------------
    
for(int i = 0; i < 25; i++) {   // initally 0 of each card
    counts[i] = 0;
}

srand (time(NULL));             // random seed
int card;
for(int i = 0; i < 71; i++) {   // put 71 cards into the deck
   
    do{
        card = rand() % 24 + 1;                             // generate random card
    } while ( counts[ card ] >= maxCounts[  card ] );       // only use cards we need
    
    deck.push( card );
    counts[ card ]++;
    cards_in_deck++;
}
board->set(5, 5, 4);            // put starting tile onto the board

}
