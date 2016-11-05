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
}
