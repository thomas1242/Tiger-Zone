#include "board.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Board::Board(card) {                        // board constructor
    
    cout << "Put center card on board" << endl;
    possibleMoves[ROWS/2][COLS/2] = true;                        // mark center location available
    
    placeCard(ROWS/2, COLS/2, card);        // place center card on the board
    board = new Card * [ROWS];              // board is initially all open space ( cards with id = -1 )
    for(int i = 0; i < ROWS; ++i) {
        board[i] = new Card[COLS];
    }
}
    

bool Board::placeCard(int i, int j, Card* card) {
    
    if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  // for GUI, if user clicks out of bounds
        return false;
    }
    
    // before placing this card on the board, make sure the location is valid
    if( !(board[i][j].isfiller) ) {
       cout << "Cannot place card " << card->getId() << " at (" << i << ',' << j << ']' << endl;
       return false;
    }

// Match it with avail side
/*    
   while( !checkIfFits(i, j, card) ) {
        card->rotate();                     // rotate card until it fits at the valid location
    }
*/    
    else {
        cout << "Placed card " << card->getId() << " at [" << i << ',' << j << ']' << endl;
        board[i][j] = *card;            // replace with new card
        markavail(i, j, card);
        
        printBoard();
        return true;
    }
}
    

// bool place meeple()

/*
void Board::updatePossibleMoves(Card * card) { // possible moves based on board state and current card
    
    for(int i = 0; i < ROWS; i++) {     
        for(int j = 0; j < COLS; j++) {
            if(board[i][j].getId() == -1) {                                  // if this spot is not taken (open space)
                if(i - 1 > 0 && board[i - 1][j].getId() != -1) {             // and is adjacent to a taken spot
                    possibleMoves[i][j] = true;
                }
                else if(i + 1 < ROWS && board[i + 1][j].getId() != -1) {
                    possibleMoves[i][j] = true;
                }
                else if(j - 1 > 0 && board[i][j - 1].getId() != -1) {
                    possibleMoves[i][j] = true;
                }
                else if(j + 1 < COLS && board[i][j + 1].getId() != -1) {
                    possibleMoves[i][j] = true;
                }
            }
            else {
                possibleMoves[i][j] = false;
            }
        }
    }
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if( possibleMoves[i][j] == true ) { // if this spot is potentially valid (it's adjacent to another tile)
                int n = 1;
                while(n <= 4) {                          // 0, 90, 180, 270
                    if(checkIfFits(i, j, card)) {
                        break;
                    }
                    card->rotate();
                    n++;
                }
                if( n > 4) {
                    possibleMoves[i][j] = false;;
                }
                else {
                    possibleMoves[i][j] = true;
                }
            }
        }
    }

}
*/

>>>>>>> sfmlBranch
bool Board::checkIfFits(int i, int j, Card * card ) {   // i is row, j is col
    
    bool result = true;
    
    // check that the sides match OR are next to open space
    
    // there is no tile above, tile above matches the top, tile above is open space
    if(i == 0 || card->getTop() == board[i-1][j].getBot() || board[i-1][j].getBot() == 'o') {              // check top side
        result = false;
    }
    // there is no tile below, tile below matches the bot, tile below is open space
    if(i == ROWS - 1 || card->getBot() == board[i+1][j].getTop() || board[i+1][j].getTop() == 'o') {         // check bot side
        result = false;
    }
    // there is no tile on right, tile on right matches the right, right tile is open space
    if(j == COLS - 1 || card->getRight() == board[i][j+1].getLeft() || board[i][j+1].getLeft() == 'o') {         // check right side
        result = false;
    }
    // there is no tile on left, tile on left matches the left, left tile is open space
    if(j == 0 || card->getLeft() == board[i][j-1].getRight() || board[i][j-1].getRight() == 'o') {         // check left side
        result = false;
    }
    
    return result;
}

// Mark available spots for the board
void Board::markavail(int i, int j, Card* card) {
	//Marking space above
	if(i > 0 && board[i-1][j].isfiller) {			
		//check to see if card is already there, discuss how to mark terrain
		board[i-1][j].a_bot = card->getTop();
        possibleMoves[i-1][j] = true;
	}	

	//Marking space below
	if(i < ROWS-1 && board[i+1][j].isfiller) {
		//check to see if card is already there, discuss what to mark terrain
		board[i+1][j].a_top = card->getBot();
        possibleMoves[i+1][j] = true;
	}
	
	//Marking space on left
	if(j > 0 && board[i][j-1].isfiller) {
		//check to see if card is already there, discuss what to mark terrain
		board[i][j-1].a_right = card->getLeft();
        possibleMoves[i][j-1] = true;
	}
	
	//Marking space on right
	if(j < COLS-1 && board[i][j+1].isfiller) {
		//check to see if card is already there, discuss what to nark terrain
		board[i][j+1].a_left = card->getRight();
        possibleMoves[i][j+1] = true;
	}	
}


/*  TL  TOP  TR
    ML  MID  MR
    BL  BOT  BR   */
void Board::printBoard() {
    cout << "\nTHE BOARD: " << endl;
    for(int i = 0; i < ROWS; i++) {           	// for each row
        for(int n = 0; n < 3; n++) {        	// 3 'rows' per row
            for(int j = 0; j < COLS; j++) {   	// for each col
                if(n == 0) {
                    cout << board[i][j].getTop_L() << ' ' << board[i][j].getTop() << ' ' << board[i][j].getTop_R() << ' ';
                }
                else if (n == 1) {
                    cout << board[i][j].getLeft() << ' ' << board[i][j].getMid() << ' ' << board[i][j].getRight() << ' ';
                }
                else if (n == 2) {
                    cout << board[i][j].getBot_L() << ' ' << board[i][j].getBot() << ' ' << board[i][j].getBot_R() << ' ';
                }
                cout << ' ';
            }
            if( n == 1 ) {
                for(int k = 0; k < COLS; k++) {
                    cout << "  " << board[i][k].getId() << "  ";
                }
            }
           cout << endl;
        }
        cout << endl;
    }
  
    // print possibleMoves array underneath the board!
    cout << "\nPOSSIBLE MOVES: " << endl;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            cout << ' ' << possibleMoves[i][j] << "  ";
        }
        cout << endl;
    }
    
}

Deck * Board::getDeck() {   // return pointer to the deck
    return theDeck;
}

Card Board::getCard(int i, int j) {
    return board[i][j];
}

bool Board::checkPossibleMove(int i, int j) {
    return possibleMoves[i][j];
}

bool * Board::getPossibleMoves() {
    return (bool*)possibleMoves;
}

bool Board::isPossibleMove() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(possibleMoves[i][j] == true) {
                return true;
            }
        }
    }
    return false;
}









