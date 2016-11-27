#include "game.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <string>
using namespace std;

int main() {
    
    Game * game = new Game();               // create the game
    game->startGame();
    int row, col;
    string choice;
    
    
    
    
    
    while ( game->status() == ON )  // Start the game loop
    {      
        game->giveCard();   // draw a card if the player needs    

        if ( game->getCurrTurn() ) { cout << "\nPlayer 1's turn" << endl; }
        else                       { cout << "\nPlayer 2's turn" << endl; }
        cout << "enter '0' to place current card on the board" << endl;
        cout << "enter '1' to rotate current card" << endl;
        cout << "enter '2' to print the board\n" << endl;
        
        cin >> choice;

        if ( choice == "0" ) {
            cout << "row? ";
            cin >> row;
            cout << "col? ";
            cin >> col;
            game->giveTurn(row, col);
        }
        else if( choice == "1") {
            game->rotateCard();
        }
        else if( choice == "2") {
            game->printBoard();
        }
    }

    return 0;
}
