#include "game.h"
#include <iostream>
using namespace std;

Game::Game() {
    
    isActive = OFF;
    board = new Board();                   // the board
    player_one = new Player( board );      // player 1 knows about the board
    player_two = new Player( board );      // player 2 knows about the board
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
    this->~Game();      // delete the game
}

void Game::playTurn() {
    
    if( board->getDeck()->isEmpty() )    // if the deck is empty, game is over
        endGame();
    else if( current_turn )              // player one makes a move
        player_one->takeTurn();
    else
        player_two->takeTurn();          // player two makes a move
    
    current_turn = !current_turn;        // toggle turn
}



