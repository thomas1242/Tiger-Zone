#include "deck.h"
#include "card.h"
#include "board.h"
#include "player.h"
#include <iostream>

using namespace std;


int main() {
    
    Board  * b = new Board();           
    Player * p = new Player( b );
    
    p->takeTurn();
    
    return 0;
}
