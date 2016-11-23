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
    game1->startGame();
    int row, col;
    int choice = 0;
    while ( game1->status() == ON )  // Start the game loop
    {      
        game1->giveCard();   // draw a card if the player needs    

        if ( game1->getCurrTurn() ) { cout << "player 1's turn" << endl; }
        else                       { cout << "player 2's turn" << endl; }
        cout << "Enter '1' to place a card on the board" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "row? ";
            cin >> row;
            cout << "col? ";
            cin >> col;
            game1->giveTurn(row, col);
            
            choice = 0;
        }
    }

    return 0;
}
