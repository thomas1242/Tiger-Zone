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



Board::Board() {                       // new board initially empty
	
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
