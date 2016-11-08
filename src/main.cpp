#include "game.h"
using namespace std;

int main() {
    
    Game * game = new Game();               // create the game
    
    game->startGame();                      // start the game
    
    while( game->status() == ON ) {         // while the game is not over
        game->playTurn();                   // players take turns making moves
    }

    return 0;
}
