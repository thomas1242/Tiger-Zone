//
//  game.cpp
//  testingTiger
//
//  Created by Thomas Palmer on 11/8/16.
//  Copyright © 2016 blank. All rights reserved.
//

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

void Game::playTurn(){
    if( board->getDeck()->isEmpty() )    // if the deck is empty, game is over
        endGame();
    else if( current_turn && player_one->hasCard == false && player_two->hasCard == false) {             // player one makes a move
        cout << "player_one to draw card:" << endl;
        player_one->drawCard();
    }
    else if ( !current_turn && player_one->hasCard == false && player_two->hasCard == false) {
        cout << "player_two to draw card:" << endl;
        player_two->drawCard();          // player two makes a move
    }
}

void Game::playTurn(int i, int j) {

    
    if( current_turn && player_one->hasCard == true)  {            // player one makes a move
        if(player_one->takeTurn(i, j))
            current_turn = !current_turn;        // toggle turn
    }
    else if ( !current_turn && player_two->hasCard == true ) {
        if (player_two->takeTurn(i, j))
            current_turn = !current_turn;        // toggle turn
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

Player * Game::getPlayer() {
    if ( current_turn ) {
        return player_one;
    }
    else {
        return player_two;
    }
}

