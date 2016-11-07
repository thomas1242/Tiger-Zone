#include "main.h"
#include "board.h"
#include <stdio.h>
#include <iostream>
using namespace std;
// Internal representation of the state of the board.
//
//    0 = empty space
//    n = tile n
//   25 = valid move for the current players turn and tile

#define boardsize decksize*2+1		// variable for board length;

Board::Board() {                       
}


// Mark available spots for the board
void Board::markavail(int xcoord, int ycoord) {
	//Marking space above
	if(xcoord > 0) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord-1][ycoord] = new card(0);
		matrix[xcoord-1][ycoord]->avail_bot = matrix[xcoord][ycoord]->top;
	}	

	//Marking space below
	if(xcoord < boardlength) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord+1][ycoord] = new card(0);
		matrix[xcoord+1][ycoord]->avail_top = matrix[xcoord][ycoord]->bot;
	}
	
	//Marking space on left
	if(ycoord > 0) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord][ycoord-1] = new card(0);
		matrix[xcoord][ycoord-1]->avail_right = matrix[xcoord][ycoord]->left;
	}
	
	//Marking space on right
	if(ycoord < boardlength) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord][ycoord+1] = new card(0);
		matrix[xcoord][ycoord+1]->avail_left = matrix[xcoord][ycoord]->right;
	}	
}

bool Board::checkspace(int xcoord, int ycoord) {

}

// Place tile on board at specified location
bool Board::place(int xcoord, int ycoord, Card input) {
	if(checkspace[xcoord][ycoord] == true) {
		//Place it
	}
	else {
		//Don't do anything, return false
	}
}

void Board::printBoard(){
    cout << endl;
    for(int i = 0; i < boardlength; i++){
        for(int j = 0; j < boardlength; j++){
            printf ("%3d ", board[i][j]);
        }
        cout << endl;
    }
    cout << endl;

}
