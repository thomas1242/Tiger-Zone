#include "board.h"
#include "card.h"
#include <iostream>
using namespace std;

Board::Board() {                                // board constructor
    
    int rowCount = 10;
    int colCount = 10;
    
    board = new Card * [rowCount];              // board is initially all open space ( cards with id = -1 )
    for(int i = 0; i < rowCount; ++i) {
       board[i] = new Card[colCount];
    }
}


/*            TOP
    Print LEFT   RIGHT matrix and the id matrix side by side easy debugging
              BOT
*/
void Board::printBoard() {
    
    for(int i = 0; i < 10; i++) {           // for each row
        for(int n = 0; n < 3; n++) {        // 3 'rows' per row
            for(int j = 0; j < 10; j++) {   // for each col
                if(n == 0) {
                    cout << ' ' << board[i][j].getTop() << ' ';
                }
                else if (n == 1) {
                    cout << board[i][j].getLeft() << ' ' << board[i][j].getRight();
                }
                else if (n == 2) {
                    cout << ' ' << board[i][j].getBot() << ' ';
                }
                cout << ' ';
            }
            if( n == 1 ) {
                for(int k = 0; k < 10; k++) {
                    cout << "   " << board[i][k].getId() << "   ";
                }
            }
           cout << endl;
        }
    }
    
}








