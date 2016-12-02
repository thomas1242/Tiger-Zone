
#include "game.h"
#include "card.h"
#include "board.h"
#include "game.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(Card *tile, int x, int y, int orientation) {
    isActive = OFF;
    //deck = new Deck();
    board = new Board(tile, x, y, orientation );       // the board
    player_one = new Player( board, 1 );      // player 1 knows the board and deck
    player_two = new Player( board, 2 );      // player 2 knows the board and deck
    current_turn = true; // player 1's turn
}

Game::~Game() {
    
    delete board;
    delete player_one;
    delete player_two;
}

int Game::convertID(string ID)
{
    if(ID == "JJJJ-"){return 0;}
    if(ID == "JJJJX"){return 1;}
    if(ID == "JJTJX"){return 2;}
    if(ID == "TTTT-"){return 3;}
    if(ID == "TJTJ-"){return 4;}
    if(ID == "TJJT-"){return 5;}
    if(ID == "TJTT-"){return 6;}
    if(ID == "LLLL-"){return 7;}
    if(ID == "JLLL-"){return 8;}
    if(ID == "LLJJ-"){return 9;}
    if(ID == "JLJL-"){return 10;}
    if(ID == "LJLJ-"){return 11;}
    if(ID == "LJJJ-"){return 12;}
    if(ID == "JLLJ-"){return 13;}
    if(ID == "TLJT-"){return 14;}
    if(ID == "TLJTP"){return 15;}
    if(ID == "JLTT-"){return 16;}
    if(ID == "JLTTB"){return 17;}
    if(ID == "TLTJ-"){return 18;}
    if(ID == "TLTJD"){return 19;}
    if(ID == "TLLL-"){return 20;}
    if(ID == "TLTT-"){return 21;}     
    if(ID == "TLTTP"){return 22;}
    if(ID == "TLTT-"){return 23;}
    if(ID == "TLLTB"){return 24;}
    if(ID == "LJTJ-"){return 25;}
    if(ID == "LJTJD"){return 26;}
    if(ID == "TLLLC"){return 27;}
    else return -1;
}

bool Game::status() {
    return isActive;
}

void Game::startGame() {
    isActive = ON;    // start the game
}

void Game::endGame() {
    isActive = OFF;    // start the game
    // this->~Game();      // delete the game
}

void Game::giveCard(string ID, Input *in) {
    
    if( current_turn && player_one->hasCard == false && player_two->hasCard == false) {             // player one makes a move
        //cout << "player_one to draw card:" << endl;
        player_one->takeCard(ID, in);
    }
    else if ( !current_turn && player_one->hasCard == false && player_two->hasCard == false) {
        //cout << "player_two to draw card:" << endl;
        player_two->takeCard(ID, in);          // player two makes a move
    }
    
}

void Game::giveTurn(int x, int y) {
   /* 
    if( deck->isEmpty() ) {    // if final card was played
        endGame();
        cout << "DECK EMPTY -> GAME OVER!";
        return;
    }*/
    if ( current_turn && player_one->hasCard == true)  {            // player one makes a move
        if(player_one->takeTurn(x, y))
            current_turn = !current_turn;        // toggle turn
        else{}
            //cout << "Cannot place card " << getCurrCardID() << " at (" << i << ',' << j << ']' << endl;
        
    }
    else if ( !current_turn && player_two->hasCard == true ) {
        if (player_two->takeTurn(x, y))
            current_turn = !current_turn;        // toggle turn
        else{}
            //cout << "Cannot place card " << getCurrCardID() << " at (" << i << ',' << j << ']' << endl;
    }
}

Board * Game::getBoard() {
    return board;
}

int Game::getCurrCardID() {
    if( player_one->hasCard == true)              // player one makes a move
        return  player_one->getCardId();
    else if (player_two->hasCard == true) {
        return  player_two->getCardId();
    }
    else return -1;
}

void Game::rotateCard() {
    if ( current_turn ) {
        player_one->rotateCard();
    }
    else {
        player_two->rotateCard();
    }
}

Player * Game::getCurrPlayer() {
    if ( current_turn ) {
        return player_one;
    }
    else {
        return player_two;
    }
}

bool Game::getCurrTurn() {
    return current_turn;
}

int Game::getScore( bool player ) {
    if(player) {
        return player_one->getScore();
    }
    else {
        return player_two->getScore();
    }
}

int Game::getTigers( bool player ) {
    if(player) {
        return player_one->getTigers();
    }
    else {
        return player_two->getTigers();
    }
}

void Game::printBoard() {
    board->printBoard();
}

//for gui
Card * Game::getCurrCard() {
    if ( current_turn ) {
        return player_one->getCard();
    }
    else {
        return player_two->getCard();
    }
}
/*
Deck * Game::getDeck() {
    return deck;
}*/

void Game::setStartingPlayer(bool us) {
    if(us){
        current_turn = true;
    }
    else {
        current_turn = false;
    }
}





