#include "game.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main() {
    
    Game * game1 = new Game();               // create the game
    Game * game2 = new Game();               // create the game
    cout << "past game"  << endl;
    game->startGame();
    int row, col;
    int choice = 0;
    while ( game->status() == ON )  // Start the game loop
    {      
        game->giveCard();   // draw a card if the player needs    

        if ( game->getCurrTurn() ) { cout << "player 1's turn" << endl; }
        else                       { cout << "player 2's turn" << endl; }
        cout << "Enter '1' to place a card on the board" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "row? ";
            cin >> row;
            cout << "col? ";
            cin >> col;
            game->giveTurn(row, col);
            
            choice = 0;
        }
    }

    return 0;
}
