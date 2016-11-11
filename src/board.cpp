#include "board.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Board::Board() {                            // board constructor
    
    theDeck = new Deck();                   // new board comes with a new deck
//***   
// Kurt - Didn't we decide on not initializing whole board? This was for efficiency

    board = new Card * [ROWS];              // board is initially all open space ( cards with id = -1 )
    for(int i = 0; i < ROWS; ++i) {
        board[i] = new Card[COLS];
        for(int j = 0; j < COLS; j++) {
//***


// Kurt - I feel like this should be a list or 1D array of coordinates. I don't see how this makes it easier to search board
// If we want the 2D array, I feel that we should just make it a card variable for efficiency.
            possibleMoves[i][j] = false;    // initalize possible moves
        }
    }

// Kurt - Removed division calculations and replaced with MAXCARDS
    possibleMoves[MAXCARDS][MAXCARDS] = true;                        // mark center location available
    placeCard(MAXCARDS, MAXCARDS, new Card( theDeck->drawCard() ));  // place center card on the board
}
    

bool Board::placeCard(int i, int j, Card* card) {
    
    // before placing this card on the board, make sure the location is valid
    if( !possibleMoves[i][j] ) {
       cout << "Cannot place card " << card->getId() << " at [" << i << ',' << j << ']' << endl;
       return false;
    }
    
    cout << "Placed card " << card->getId() << " at [" << i << ',' << j << ']' << endl;
    board[i][j] = card;            // replace with new card
//******************************************************************************************************
// Kurt - we should mark available spots here
//******************************************************************************************************
    markavail(i, j);
    return true;
}

bool Board::checkIfFits(int i, int j, Card * card ) {   // i is row, j is col
    
    bool result = false;
    
    // check that the sides match OR are next to open space
    
    // there is no tile above, tile above matches the top, tile above is open space
    if(i == 0 || card->getTop() == board[i-1][j].getBot() || board[i-1][j].getBot() == 'o') {              // check top side
        result = true;
    }
    // there is no tile below, tile below matches the bot, tile below is open space
    if(i == ROWS - 1 || card->getBot() == board[i+1][j].getTop() || board[i+1][j].getTop() == 'o') {         // check bot side
        result = true;
    }
    // there is no tile on right, tile on right matches the right, right tile is open space
    if(j == COLS - 1 || card->getRight() == board[i][j+1].getLeft() || board[i][j+1].getLeft() == 'o' ) {         // check right side
        result = true;
    }
    // there is no tile on left, tile on left matches the left, left tile is open space
    if(j == 0 || card->getLeft() == board[i][j-1].getRight() || board[i][j-1].getRight() == 'o' ) {         // check left side
        result = true;
    }
    
    return result;
}


// Kurt - This code is really innefficient. See markavail function below
// We should probably rework/remove this********************************************


/*void Board::updatePossibleMoves(Card * card) { // possible moves based on board state and current card
    
// Kurt - Why loop through whole array? We only are looking at cards around placed tiles. Super inefficient
// We should set possible moves when we place card. Will never change otherwise.
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
                if( !checkIfFits(i, j, card) ) { // check if card fits at this location. if not, this move isn't valid!
                    possibleMoves[i][j] = false;
                }
            }
        }
    }

}*/

// Kurt - Why don't we use the deleted code instead? It's more efficient, just needs to be updated to fit our stuff
// Fits directly into the place card function


// Kurt - Need to talk about this convention.. Are unmarked spaces null or blank?
// Mark available spots for the board
void Board::markavail(int xcoord, int ycoord, Card card) {
	//Marking space above
	if(xcoord > 0 && matrix[xcoord-1][ycoord] == 0) {			
		//check to see if card is already there, discuss what to do
		matrix[xcoord-1][ycoord] = new card();
		matrix[xcoord-1][ycoord]->avail_bot = matrix[xcoord][ycoord]->top;
	}	

	//Marking space below
	if(xcoord < boardsize && matrix[xcoord+1][ycoord] == 0) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord+1][ycoord] = new card();
		matrix[xcoord+1][ycoord]->avail_top = matrix[xcoord][ycoord]->bot;
	}
	
	//Marking space on left
	if(ycoord > 0 && matrix[xcoord][ycoord-1] == 0) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord][ycoord-1] = new card();
		matrix[xcoord][ycoord-1]->avail_right = matrix[xcoord][ycoord]->left;
	}
	
	//Marking space on right
	if(ycoord < boardsize && matrix[xcoord][ycoord+1] == 0) {
		//check to see if card is already there, discuss what to do
		matrix[xcoord][ycoord+1] = new card();
		matrix[xcoord][ycoord+1]->avail_left = matrix[xcoord][ycoord]->right;
	}	
}


/*            TOP
    Print LEFT   RIGHT matrix and the id matrix side by side easy debugging
              BOT
*/
void Board::printBoard() {
    
    
    cout << "\nTHE BOARD: " << endl;
    for(int i = 0; i < ROWS; i++) {           // for each row
        for(int n = 0; n < 3; n++) {        // 3 'rows' per row
            for(int j = 0; j < COLS; j++) {   // for each col
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
                for(int k = 0; k < COLS; k++) {
                    cout << "  " << board[i][k].getId() << "  ";
                }
            }
           cout << endl;
        }
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










