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



Board::Board() {                       
}


// Mark available spots for the board
void Board::markavail(int xcoord, int ycoord, Card* matrix[][boardlength]) {
	

	if(xcoord > 0) {
		matrix[xcoord-1][ycoord] = new card(2);
		//matrix[xcoord-1][ycoord]->top = 'i';
	}	

	if(xcoord < boardlength) {
		matrix[xcoord+1][ycoord] = new card(3);
		//matrix[xcoord+1][ycoord]->top = 'g';
	}
	
	if(ycoord > 0) {
		matrix[xcoord][ycoord-1] = new card(4);
		//matrix[xcoord][ycoord-1]->top = 'h';
	}
	
	if(ycoord < boardlength) {
		matrix[xcoord][ycoord+1] = new card(5);
		//matrix[xcoord][ycoord+1]->top = 't';
	}	
}

// Place tile on board at specified location
int Board::place(int xcoord, int ycoord, Card input) {

}

void Board::printBoard(){
    cout << endl;
    for(int i = 0; i < size*2+1; i++){
        for(int j = 0; j < size*2+1; j++){
            printf ("%3d ", board[i][j]);
        }
        cout << endl;
    }
    cout << endl;

}
