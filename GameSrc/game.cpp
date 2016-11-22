
#include "game.h"
#include <iostream>
using namespace std;

Game::Game() {
    isActive = OFF;
    deck = new Deck();
    board = new Board( deck->drawCard() );       // the board
    player_one = new Player( board, deck );      // player 1 knows the board and deck
    player_two = new Player( board, deck );      // player 2 knows the board and deck
    current_turn = true; // player 1's turn
}

Game::~Game() {
    
    delete board;
    delete player_one;
    delete player_two;
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

void Game::giveCard() {
    
    if( current_turn && player_one->hasCard == false && player_two->hasCard == false) {             // player one makes a move
        cout << "player_one to draw card:" << endl;
        player_one->takeCard();
    }
    else if ( !current_turn && player_one->hasCard == false && player_two->hasCard == false) {
        cout << "player_two to draw card:" << endl;
        player_two->takeCard();          // player two makes a move
    }
    
}

void Game::giveTurn(int i, int j) {

    
    if( current_turn && player_one->hasCard == true)  {            // player one makes a move
        if(player_one->takeTurn(i, j))
            current_turn = !current_turn;        // toggle turn
    }
    else if ( !current_turn && player_two->hasCard == true ) {
        if (player_two->takeTurn(i, j))
            current_turn = !current_turn;        // toggle turn
    }
    
    if( deck->isEmpty() ) {    // if final card was played
        endGame();
        cout << "DECK EMPTY -> GAME OVER!";
        return;
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

int Game::getMeeples( bool player ) {
    if(player) {
        return player_one->getMeeples();
    }
    else {
        return player_two->getMeeples();
    }
}
