#include "deck.h"
#include "card.h"
#include "board.h"

using namespace std;


int main() {
    
    Deck * d = new Deck();
    Card * c = new Card(23);
    Board * b = new Board();
    
    b->printBoard();
    
    
    
    return 0;
}
