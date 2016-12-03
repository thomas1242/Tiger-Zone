#include "board.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Board::Board(Card * card, int x, int y, int orientation) {                            // board constructor
        
    board = new Card * [ROWS];              // board is initially all open space ( cards with id = -1 )
    for(int i = 0; i < ROWS; ++i) {
        board[i] = new Card[COLS];
        for(int j = 0; j < COLS; j++) {
            possibleMoves[i][j] = false;    // initalize possible moves
        }
    }
    
    numJungles = 0;
    numTrails = 0;
    numLakes = 0;
    
    jungles = new Jungle[100];
    trails  = new Trail[100];
    lakes   = new Lake[100];
    
    for(int i = 0; i < 100; i++) {
        trails[i].setId(i);
        lakes[i].setId(i);
        jungles[i].setId(i);
    }
    
    card->orientation = orientation;
    int mapped_i = ROWS/2 - y;
    int mapped_j = COLS/2 + x;

    cout << "Put center card on new board";
    possibleMoves[mapped_i][mapped_j] = true;                        // mark center location available
    placeCard(mapped_i, mapped_j, card, 1, 0, true );        // place center card on the board
}


bool Board::placeCard(int i, int j, Card * card, int playerID, int zone, bool typeFollower) {
    
    if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  // for GUI, if user clicks out of bounds
        cout << "Cannot place card " << card->getId() << " at (" << i << ',' << j << ']' << endl;
        return false;
    }
    
    // before placing this card on the board, make sure the location is valid
    if( !possibleMoves[i][j] ) {
        cout << "Cannot place card " << card->getId() << " at (" << i << ',' << j << ']' << endl;
        return false;
    }
    
    while( !checkIfFits(i, j, card) ) {
        card->rotate();                 // rotate card until it fits at the valid location
    }
    
    connectCardtoBoard( i, j, card );   // merge with board
    
    board[i][j] = *card;                // put on board
    
    cout << board[i][j].getCardID() << " with orientation " << board[i][j].getOrient() << " placed at [" << (j-5) << "][" << -(i-5) << "] by player " << playerID << endl;
    
    int L1 = 10, L2 = 10, J1 = 10, J2 = 10, J3 = 10, J4 = 10, T1 = 10, T2 = 10, T3 = 10, T4 = 10;
    card->assignZones(L1, L2, J1, J2, J3, J4, T1, T2, T3, T4);  // print meeple locations on current card
    
    if( zone != 0) { //place follower
        placeMeeple(playerID, zone, typeFollower, card);
    }
    cout << endl;
 
    
    
     //printCardRegions(i, j);
    
     scoreMove( card, playerID );  // score card placed
    
     printFeatures();    // === increment features edges
    
    // printBoard();
    
    return true;
}

void Board::placeMeeple(int playerID, int zone, bool tiger, Card * card) {
    
    // which cell each region is located in
    int L1 = 10, L2 = 10, J1 = 10, J2 = 10, J3 = 10, J4 = 10, T1 = 10, T2 = 10, T3 = 10, T4 = 10;
    card->assignZones(L1, L2, J1, J2, J3, J4, T1, T2, T3, T4);
    if(zone > 0) {
        
        if( tiger )
            cout << "\nplacing tiger in " << zone << endl;
        else
            cout << "\nplacing crocodile in " << zone << endl;
        
        // make sure that this zone is not owned before placing a meeple here
        if (zone == L1 && card->l1 != NULL &&  lakes[  card->l1->getId() ].getOwner() == -1) {      // if valid meeple location
                lakes[  card->l1->getId() ].addMeeple(playerID);                                    // place meeple in region
        }
        else if (zone == L2 && card->l2 != NULL &&  lakes[  card->l2->getId() ].getOwner() == -1) {
                lakes[  card->l2->getId() ].addMeeple(playerID);
        }
        else if (zone == J1 && card->j1 != NULL && jungles[  card->j1->getId() ].getOwner() == -1) {
                jungles[  card->j1->getId() ].addMeeple(playerID);
        }
        else if (zone == J2 && card->j2 != NULL && jungles[  card->j2->getId() ].getOwner() == -1) {
                jungles[  card->j2->getId() ].addMeeple(playerID);
        }
        else if (zone == J3 && card->j3 != NULL && jungles[  card->j3->getId() ].getOwner() == -1) {
                jungles[  card->j3->getId() ].addMeeple(playerID);
        }
        else if (zone == J4 && card->j4 != NULL && jungles[  card->j4->getId() ].getOwner() == -1) {
                jungles[  card->j4->getId() ].addMeeple(playerID);
        }
        else if (zone == T1 && card->t1 != NULL && trails[  card->t1->getId() ].getOwner() == -1) {
                trails[  card->t1->getId() ].addMeeple(playerID);
        }
        else if (zone == T2 && card->t2 != NULL && trails[  card->t2->getId() ].getOwner() == -1) {
                trails[  card->t2->getId() ].addMeeple(playerID);
        }
        else if (zone == T3 && card->t3 != NULL && trails[  card->t3->getId() ].getOwner() == -1) {
                trails[  card->t3->getId() ].addMeeple(playerID);
        }
        else if (zone == T4 && card->t4 != NULL && trails[  card->t4->getId() ].getOwner() == -1) {
                trails[  card->t4->getId() ].addMeeple(playerID);
        }
    }
}

void Board::updatePossibleMoves(Card * card) { // possible moves based on board state and current card\
        
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

bool Board::checkIfFits(int i, int j, Card * card ) {   // i is row, j is col
    
    bool result = true;
    
    // check that the sides match OR are next to open space
    // there is no tile above, tile above matches the top, tile above is open space
    if( !(i == 0 || card->getTop() == board[i-1][j].getBot() || board[i-1][j].getBot() == 'o' ) ) {              // check top side
        result = false;
    }
    // there is no tile below, tile below matches the bot, tile below is open space
    if( !(i == ROWS - 1 || card->getBot() == board[i+1][j].getTop() || board[i+1][j].getTop() == 'o' ) ) {         // check bot side
        result = false;
    }
    // there is no tile on right, tile on right matches the right, right tile is open space
    if( !(j == COLS - 1 || card->getRight() == board[i][j+1].getLeft() || board[i][j+1].getLeft() == 'o' ) ) {         // check right side
        result = false;
    }
    // there is no tile on left, tile on left matches the left, left tile is open space
    if( !(j == 0 || card->getLeft() == board[i][j-1].getRight() || board[i][j-1].getRight() == 'o' ) ) {         // check left side
        result = false;
    }
    
    return result;
}



void Board::printBoard() {
    cout << "\nTHE BOARD: " << endl;
    for(int i = 0; i < ROWS; i++) {           // for each row
        for(int n = 0; n < 3; n++) {        // 3 'rows' per row
            for(int j = 0; j < COLS; j++) {   // for each col
                if(n == 0) {
                    cout << ' ' << ' ' << board[i][j].getTop() << ' ' << ' ' << ' ';
                }
                else if (n == 1) {
                    cout << board[i][j].getLeft() << ' ' << board[i][j].getMid() << ' ' << board[i][j].getRight() << ' ';
                }
                else if (n == 2) {
                    cout << ' ' << ' ' << board[i][j].getBot() << ' ' << ' ' << ' ';
                }
                cout << ' ';
            }
           // if( n == 1 ) {
           //     for(int k = 0; k < COLS; k++) {
           //         cout << "  " << board[i][k].getId() << "  ";
           //    }
           // }
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

int Board::getOrient(int i, int j) {
    return board[i][j].getOrient();
}

void Board::printCardRegions(int i, int j) {
    if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  
        return;
    }
    
    if(board[i][j].l1 != NULL) {
        cout << "L1 part of lake:   " << (board[i][j]).l1->getId() << endl;
    }
    if(board[i][j].l2 != NULL) {
        cout << "L2 part of lake:   " << board[i][j].l2->getId() << endl;
    }
    if(board[i][j].t1 != NULL) {
        cout << "T1 part of trail:  " << board[i][j].t1->getId() << endl;
    }
    if(board[i][j].t2 != NULL) {
        cout << "T2 part of trail: " << board[i][j].t2->getId() << endl;
    }
    if(board[i][j].t3 != NULL) {
        cout << "T3 part of trail:  " << board[i][j].t3->getId() << endl;
    }
    if(board[i][j].t4 != NULL) {
        cout << "T4 part of trail:  " << board[i][j].t4->getId() << endl;
    }
    if(board[i][j].j1 != NULL) {
        cout << "J1 part of jungle: " << board[i][j].j1->getId() << endl;
    }
    if(board[i][j].j2 != NULL) {
        cout << "J2 part of jungle: " << board[i][j].j2->getId() << endl;
    }
    if(board[i][j].j3 != NULL) {
        cout << "J3 part of jungle: " << board[i][j].j3->getId() << endl;
    }
    if(board[i][j].j4 != NULL) {
        cout << "J4 part of jungle: " << board[i][j].j4->getId() << endl;
    }
    cout << '\n' << endl;
}

void Board::printFeatures() {
   
    cout << "\nLAKES:" << endl;
    for(int i = 0; i < 100; i++) {
        if(lakes[i].numTiles > 0) {
            cout << "lakes " << i << ":" << endl;
            cout << "       numEdges = " << lakes[i].edgeConnects << endl;
            cout << "       numTiles = " << lakes[i].numTiles << endl;
            cout << "       numPrey  = " << lakes[i].preyCount << endl;
            cout << "          owner = " << lakes[i].getOwner() << endl;
        }
    }
    cout << "\nTRAILS:" << endl;
    for(int i = 0; i < 100; i++) {
        if(trails[i].numTiles > 0) {
            cout << "trails " << i << ":" << endl;
            cout << "       numEdges = " << trails[i].edgeConnects << endl;
            cout << "       numTiles = " << trails[i].numTiles << endl;
            cout << "       numPrey  = " << trails[i].preyCount << endl;
            cout << "          owner = " << trails[i].getOwner() << endl;
            cout << "          p1Tigers = " << trails[i].num_tigers_p1 << endl;

        }
    }
    cout << "\nJUNGLES:" << endl;
    for(int i = 0; i < 100; i++) {
        if(jungles[i].numTiles > 0) {
            cout << "jungles " << i << ":" << endl;
            cout << "       numEdges = " << jungles[i].edgeConnects << endl;
            cout << "       numTiles = " << jungles[i].numTiles << endl;
            cout << "          owner = " << jungles[i].getOwner() << endl;
        }
    }
    cout << "----------------------------------------------------------------\n\n" << endl;

    
}

void Board::connectCardtoBoard( int i, int j, Card * card ) {
    
    bool lakeOne = false;
    bool lakeTwo = false;
    if(card->l1 != NULL) {
        lakeOne = true;
    }
    if(card->l2 != NULL) {
        lakeTwo = true;
    }
    
    int l1_top_connect_id = -1;
    int l1_right_connect_id = -1;
    int l1_bot_connect_id = -1;
    int l1_left_connect_id = -1;
    
    int l2_top_connect_id = -1;
    int l2_right_connect_id = -1;
    int l2_bot_connect_id = -1;
    int l2_left_connect_id = -1;
    
    
    if( card->getTop() == 'L')  {                                       // this card has lake face on top edge
        
        if(i > 0 && board[i-1][j].botEdge->getType() == 'L') {          // card above has lake face on bot edge
            if(card->topEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                card->l1 = &lakes[ board[i-1][j].botEdge->l1->getId() ];
                lakeOne = false;
                l1_top_connect_id = board[i-1][j].botEdge->l1->getId();
            }
            if(card->topEdge->l1 == card->l2) {
                card->l2 = &lakes[ board[i-1][j].botEdge->l1->getId() ];
                lakeTwo = false;
                l2_top_connect_id = board[i-1][j].botEdge->l1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getBot() == 'L')  {                                       // this card has lake face on top edge
        
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'L') {          // card above has lake face on bot edge
            if(card->botEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                card->l1 = &lakes[ board[i+1][j].topEdge->l1->getId() ];
                lakeOne = false;
                l1_bot_connect_id = board[i+1][j].topEdge->l1->getId();
            }
            if(card->botEdge->l1 == card->l2) {
                card->l2 = &lakes[ board[i+1][j].topEdge->l1->getId() ];
                lakeTwo = false;
                l2_bot_connect_id = board[i+1][j].topEdge->l1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getLeft() == 'L')  {                                       // this card has lake face on top edge
        
        if(j > 0 && board[i][j-1].rightEdge->getType() == 'L') {          // card above has lake face on bot edge
            if(card->leftEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                card->l1 = &lakes[ board[i][j-1].rightEdge->l1->getId() ];
                lakeOne = false;
                l1_left_connect_id = board[i][j-1].rightEdge->l1->getId();
            }
            if(card->leftEdge->l1 == card->l2) {
                card->l2 = &lakes[ board[i][j-1].rightEdge->l1->getId() ];
                lakeTwo = false;
                l2_left_connect_id = board[i][j-1].rightEdge->l1->getId();
            }
            card->reConnect();
        }
        
    }
    
    if( card->getRight() == 'L')  {                                       // this card has lake face on top edge
        
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'L') {          // card above has lake face on bot edge
            if(card->rightEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                card->l1 = &lakes[ board[i][j+1].leftEdge->l1->getId() ];
                lakeOne = false;
                l1_right_connect_id = board[i][j+1].leftEdge->l1->getId();
            }
            if(card->rightEdge->l1 == card->l2) {
                card->l2 = &lakes[ board[i][j+1].leftEdge->l1->getId() ];
                lakeTwo = false;
                l2_right_connect_id = board[i][j+1].leftEdge->l1->getId();
            }
            card->reConnect();
        }
    }
    
    
    //@@@@@@@@@@ LAKE MERGES
    
    // -------------------------------------------------------------------------------------
    
    bool trailOne = false;
    bool trailTwo = false;
    bool trailThree = false;
    bool trailFour = false;
    
    if(card->t1 != NULL) {
        trailOne = true;
    }
    if(card->t2 != NULL) {
        trailTwo = true;
    }
    if(card->t3 != NULL) {
        trailThree = true;
    }
    if(card->t4 != NULL) {
        trailFour = true;
    }
    
    int t1_top_connect_id = -1;
    int t1_right_connect_id = -1;
    int t1_bot_connect_id = -1;
    int t1_left_connect_id = -1;
    
    int t2_top_connect_id = -1;
    int t2_right_connect_id = -1;
    int t2_bot_connect_id = -1;
    int t2_left_connect_id = -1;
    
    int t3_top_connect_id = -1;
    int t3_right_connect_id = -1;
    int t3_bot_connect_id = -1;
    int t3_left_connect_id = -1;
    
    int t4_top_connect_id = -1;
    int t4_right_connect_id = -1;
    int t4_bot_connect_id = -1;
    int t4_left_connect_id = -1;
    
    
    if( card->getTop() == 'T')  {                                       // this card has trail face on top edge
        
        if(i > 0 && board[i-1][j].botEdge->getType() == 'T') {          // card above has trail face on bot edge
            if(card->topEdge->t1 == card->t1) {     // which trail region does this cards top edge connect to
                card->t1 = &trails[ board[i-1][j].botEdge->t1->getId() ];
                trailOne = false;
                t1_top_connect_id = board[i-1][j].botEdge->t1->getId();
            }
            if(card->topEdge->t1 == card->t2) {
                card->t2 = &trails[ board[i-1][j].botEdge->t1->getId() ];
                trailTwo = false;
                t2_top_connect_id = board[i-1][j].botEdge->t1->getId();
            }
            if(card->topEdge->t1 == card->t3) {
                card->t3 = &trails[ board[i-1][j].botEdge->t1->getId() ];
                trailThree = false;
                t3_top_connect_id = board[i-1][j].botEdge->t1->getId();
            }
            if(card->topEdge->t1 == card->t4) {
                card->t4 = &trails[ board[i-1][j].botEdge->t1->getId() ];
                trailFour = false;
                t4_top_connect_id = board[i-1][j].botEdge->t1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getBot() == 'T')  {                                       // this card has trail face on bot edge
        
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'T') {          // card above has trail face on bot edge
            if(card->botEdge->t1 == card->t1) {     // which trail region does this cards top edge connect to
                card->t1 = &trails[ board[i+1][j].topEdge->t1->getId() ];
                trailOne = false;
                t1_bot_connect_id = board[i+1][j].topEdge->t1->getId();
            }
            if(card->botEdge->t1 == card->t2) {
                card->t2 = &trails[ board[i+1][j].topEdge->t1->getId() ];
                trailTwo = false;
                t2_bot_connect_id = board[i+1][j].topEdge->t1->getId();
            }
            if(card->botEdge->t1 == card->t3) {
                card->t3 = &trails[ board[i+1][j].topEdge->t1->getId() ];
                trailThree = false;
                t3_bot_connect_id = board[i+1][j].topEdge->t1->getId();
            }
            if(card->botEdge->t1 == card->t4) {
                card->t4 = &trails[ board[i+1][j].topEdge->t1->getId() ];
                trailFour = false;
                t4_bot_connect_id = board[i+1][j].topEdge->t1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getLeft() == 'T')  {                                       // this card has trail face on top edge
        
        if(j > 0 && board[i][j-1].rightEdge->getType() == 'T') {          // card above has trail face on bot edge
            if(card->leftEdge->t1 == card->t1) {     // which trail region does this cards top edge connect to
                card->t1 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
                trailOne = false;
                t1_left_connect_id = board[i][j-1].rightEdge->t1->getId();
            }
            if(card->leftEdge->t1 == card->t2) {
                card->t2 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
                trailTwo = false;
                t2_left_connect_id = board[i][j-1].rightEdge->t1->getId();
            }
            if(card->leftEdge->t1 == card->t3) {
                card->t3 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
                trailThree = false;
                t3_left_connect_id = board[i][j-1].rightEdge->t1->getId();
            }
            if(card->leftEdge->t1 == card->t4) {
                card->t4 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
                trailFour = false;
                t4_left_connect_id = board[i][j-1].rightEdge->t1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getRight() == 'T')  {                                       // this card has trail face on top edge
        
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'T') {          // card above has trail face on bot edge
            if(card->rightEdge->t1 == card->t1) {     // which trail region does this cards top edge connect to
                card->t1 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
                trailOne = false;
                t1_right_connect_id = board[i][j+1].leftEdge->t1->getId();
            }
            if(card->rightEdge->t1 == card->t2) {
                card->t2 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
                trailTwo = false;
                t2_right_connect_id = board[i][j+1].leftEdge->t1->getId();
            }
            if(card->rightEdge->t1 == card->t3) {
                card->t3 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
                trailThree = false;
                t3_right_connect_id = board[i][j+1].leftEdge->t1->getId();
            }
            if(card->rightEdge->t1 == card->t4) {
                card->t4 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
                trailFour = false;
                t4_right_connect_id = board[i][j+1].leftEdge->t1->getId();
            }
            card->reConnect();
        }
    }
    
    cout << "\n" << endl;
    
    // -------------------------------------------------------------------------------------
    
    bool jungleOne = false;
    bool jungleTwo = false;
    bool jungleThree = false;
    bool jungleFour = false;
    
    if(card->j1 != NULL) {
        jungleOne = true;
    }
    if(card->j2 != NULL) {
        jungleTwo = true;
    }
    if(card->j3 != NULL) {
        jungleThree = true;
    }
    if(card->j4 != NULL) {
        jungleFour = true;
    }
    
    
    int j1_top_connect_id = -1;
    int j1_right_connect_id = -1;
    int j1_bot_connect_id = -1;
    int j1_left_connect_id = -1;
    
    int j2_top_connect_id = -1;
    int j2_right_connect_id = -1;
    int j2_bot_connect_id = -1;
    int j2_left_connect_id = -1;
    
    int j3_top_connect_id = -1;
    int j3_right_connect_id = -1;
    int j3_bot_connect_id = -1;
    int j3_left_connect_id = -1;
    
    int j4_top_connect_id = -1;
    int j4_right_connect_id = -1;
    int j4_bot_connect_id = -1;
    int j4_left_connect_id = -1;
    
    
    
    if( card->getTop() == 'J')  {                                       // this card has jungle face on top edge
        
        if(i > 0 && board[i-1][j].botEdge->getType() == 'J') {          // card above has jungle face on bot edge
            if(card->topEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleOne = false;
                j1_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j1 == card->j2) {
                card->j2 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleTwo = false;
                j2_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j1 == card->j3) {
                card->j3 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleThree = false;
                j3_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j1 == card->j4) {
                card->j4 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleFour = false;
                j4_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getBot() == 'J')  {                                       // this card has jungle face on bot edge
        
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'J') {          // card above has jungle face on bot edge
            if(card->botEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleOne = false;
                j1_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j1 == card->j2) {
                card->j2 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleTwo = false;
                j2_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j1 == card->j3) {
                card->j3 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleThree = false;
                j3_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j1 == card->j4) {
                card->j4 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleFour = false;
                j4_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getLeft() == 'J')  {                                       // this card has jungle face on top edge
        
        if(j > 0 && board[i][j-1].rightEdge->getType() == 'J') {          // card above has jungle face on bot edge
            if(card->leftEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleOne = false;
                j1_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j1 == card->j2) {
                card->j2 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleTwo = false;
                j2_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j1 == card->j3) {
                card->j3 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleThree = false;
                j3_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j1 == card->j4) {
                card->j4 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleFour = false;
                j4_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getRight() == 'J')  {                                       // this card has jungle face on top edge
        
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'J') {          // card above has jungle face on bot edge
            if(card->rightEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleOne = false;
                j1_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j1 == card->j2) {
                card->j2 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleTwo = false;
                j2_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j1 == card->j3) {
                card->j3 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleThree = false;
                j3_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j1 == card->j4) {
                card->j4 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleFour = false;
                j4_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    cout << "\n\n" << endl;
    
    // ------------------------------------------------------------------------------------------
    
    
    if( card->getTop() == 'T')  {                                       // this card has trail face on top edge
        
        if(i > 0 && board[i-1][j].botEdge->getType() == 'T') {          // card above has trail face on bot edge
            
            if(card->topEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i-1][j].botEdge->j2->getId() ];
                jungleOne = false;
                j1_top_connect_id = board[i-1][j].botEdge->j2->getId();
            }
            if(card->topEdge->j1 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i-1][j].botEdge->j2->getId() ];
                jungleTwo = false;
                j2_top_connect_id = board[i-1][j].botEdge->j2->getId();
            }
            if(card->topEdge->j1 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i-1][j].botEdge->j2->getId() ];
                jungleThree = false;
                j3_top_connect_id = board[i-1][j].botEdge->j2->getId();
            }
            if(card->topEdge->j1 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i-1][j].botEdge->j2->getId() ];
                jungleFour = false;
                j4_top_connect_id = board[i-1][j].botEdge->j2->getId();
            }
            
            if(card->topEdge->j2 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleOne = false;
                j1_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j2 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleTwo = false;
                j2_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j2 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleThree = false;
                j3_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            if(card->topEdge->j2 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i-1][j].botEdge->j1->getId() ];
                jungleFour = false;
                j4_top_connect_id = board[i-1][j].botEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getBot() == 'T')  {                                       // this card has trail face on top edge
        
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'T') {          // card above has trail face on bot edge
            
            if(card->botEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i+1][j].topEdge->j2->getId() ];
                jungleOne = false;
                j1_bot_connect_id = board[i+1][j].topEdge->j2->getId();
            }
            if(card->botEdge->j1 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i+1][j].topEdge->j2->getId() ];
                jungleTwo = false;
                j2_bot_connect_id = board[i+1][j].topEdge->j2->getId();
            }
            if(card->botEdge->j1 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i+1][j].topEdge->j2->getId() ];
                jungleThree = false;
                j3_bot_connect_id = board[i+1][j].topEdge->j2->getId();
            }
            if(card->botEdge->j1 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i+1][j].topEdge->j2->getId() ];
                jungleFour = false;
                j4_bot_connect_id = board[i+1][j].topEdge->j2->getId();
            }
            
            if(card->botEdge->j2 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleOne = false;
                j1_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j2 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleTwo = false;
                j2_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j2 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleThree = false;
                j3_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            if(card->botEdge->j2 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i+1][j].topEdge->j1->getId() ];
                jungleFour = false;
                j4_bot_connect_id = board[i+1][j].topEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    if( card->getLeft() == 'T')  {                                       // this card has trail face on top edge
        
        if(j > 0 && board[i][j-1].rightEdge->getType() == 'T') {          // card above has trail face on bot edge
            
            if(card->leftEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j-1].rightEdge->j2->getId() ];
                jungleOne = false;
                j1_left_connect_id = board[i][j-1].rightEdge->j2->getId();
            }
            if(card->leftEdge->j1 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i][j-1].rightEdge->j2->getId() ];
                jungleTwo = false;
                j2_left_connect_id = board[i][j-1].rightEdge->j2->getId();
            }
            if(card->leftEdge->j1 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i][j-1].rightEdge->j2->getId() ];
                jungleThree = false;
                j3_left_connect_id = board[i][j-1].rightEdge->j2->getId();
            }
            if(card->leftEdge->j1 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i][j-1].rightEdge->j2->getId() ];
                jungleFour = false;
                j4_left_connect_id = board[i][j-1].rightEdge->j2->getId();
            }
            
            if(card->leftEdge->j2 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleOne = false;
                j1_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j2 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleTwo = false;
                j2_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j2 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleThree = false;
                j3_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            if(card->leftEdge->j2 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i][j-1].rightEdge->j1->getId() ];
                jungleFour = false;
                j4_left_connect_id = board[i][j-1].rightEdge->j1->getId();
            }
            card->reConnect();
        }
    }
    
    
    if( card->getRight() == 'T')  {                                       // this card has trail face on top edge
        
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'T') {          // card above has trail face on bot edge
            
            if(card->rightEdge->j1 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j+1].leftEdge->j2->getId() ];
                jungleOne = false;
                j1_right_connect_id = board[i][j+1].leftEdge->j2->getId();
            }
            if(card->rightEdge->j1 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i][j+1].leftEdge->j2->getId() ];
                jungleTwo = false;
                j2_right_connect_id = board[i][j+1].leftEdge->j2->getId();
            }
            if(card->rightEdge->j1 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i][j+1].leftEdge->j2->getId() ];
                jungleThree = false;
                j3_right_connect_id = board[i][j+1].leftEdge->j2->getId();
            }
            if(card->rightEdge->j1 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i][j+1].leftEdge->j2->getId() ];
                jungleFour = false;
                j4_right_connect_id = board[i][j+1].leftEdge->j2->getId();
            }
            
            if(card->rightEdge->j2 == card->j1) {     // which jungle region does this cards top edge connect to
                card->j1 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleOne = false;
                j1_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j2 == card->j2) {     // which jungle region does this cards top edge connect to
                card->j2 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleTwo = false;
                j2_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j2 == card->j3) {     // which jungle region does this cards top edge connect to
                card->j3 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleThree = false;
                j3_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            if(card->rightEdge->j2 == card->j4) {     // which jungle region does this cards top edge connect to
                card->j4 = &jungles[ board[i][j+1].leftEdge->j1->getId() ];
                jungleFour = false;
                j4_right_connect_id = board[i][j+1].leftEdge->j1->getId();
            }
            
            card->reConnect();
        }
        
    }
    
    if(trailOne) {
        numTrails++;
        card->t1 = &trails[ numTrails ];
        card->reConnect();
    }
    if(trailTwo) {
        numTrails++;
        card->t2 = &trails[ numTrails ];
        card->reConnect();
    }
    if(trailThree) {
        numTrails++;
        card->t3 = &trails[ numTrails ];
        card->reConnect();
    }
    if(trailFour) {
        numTrails++;
        card->t4 = &trails[ numTrails ];
        card->reConnect();
    }
    
    if(lakeOne) {
        numLakes++;
        card->l1 = &lakes[ numLakes ];
        card->reConnect();
    }
    if(lakeTwo) {
        numLakes++;
        card->l2 = &lakes[ numLakes ];
        card->reConnect();
    }
    
    if(jungleOne) {
        numJungles++;
        card->j1 = &jungles[ numJungles ];
        card->reConnect();
    }
    if(jungleTwo) {
        numJungles++;
        card->j2 = &jungles[ numJungles ];
        card->reConnect();
    }
    if(jungleThree) {
        numJungles++;
        card->j3 = &jungles[ numJungles ];
        card->reConnect();
    }
    if(jungleFour) {
        numJungles++;
        card->j4 = &jungles[ numJungles ];
        card->reConnect();
    }
    
    
    incrementEdges(i, j, card);

    
    // @@@@@@@@@@
    
    // merge t1
    if(t1_top_connect_id != t1_right_connect_id && t1_top_connect_id != -1 && t1_right_connect_id != -1 ) {
        //  //trails[ t1_right_connect_id ] = trails[ t1_top_connect_id ];
        mergeTrails( t1_right_connect_id, t1_top_connect_id );
        t1_right_connect_id = t1_top_connect_id;
    }
    if(t1_top_connect_id != t1_left_connect_id && t1_top_connect_id != -1 && t1_left_connect_id != -1 ) {
        //  trails[ t1_left_connect_id ] = trails[ t1_top_connect_id ];
        mergeTrails( t1_left_connect_id, t1_top_connect_id);
        t1_left_connect_id = t1_top_connect_id;
    }
    if(t1_top_connect_id != t1_bot_connect_id && t1_top_connect_id != -1 && t1_bot_connect_id != -1 ) {
        //trails[ t1_bot_connect_id ] = trails[ t1_top_connect_id ];
        mergeTrails( t1_bot_connect_id, t1_top_connect_id);
        l1_bot_connect_id = t1_top_connect_id;
    }
    
    if(t1_left_connect_id != t1_bot_connect_id && t1_left_connect_id != -1 && t1_bot_connect_id != -1 ) {
        // trails[ t1_bot_connect_id ] = trails[ t1_left_connect_id ];
        mergeTrails( t1_bot_connect_id, t1_left_connect_id);
        t1_bot_connect_id = t1_left_connect_id;
    }
    if(t1_right_connect_id != t1_bot_connect_id && t1_right_connect_id != -1 && t1_bot_connect_id != -1 ) {
        // trails[ t1_bot_connect_id ] = trails[ t1_right_connect_id ];
        mergeTrails( t1_bot_connect_id, t1_right_connect_id );
        t1_bot_connect_id = t1_right_connect_id;
    }
    
    if(t1_left_connect_id != t1_right_connect_id && t1_left_connect_id != -1 && t1_right_connect_id != -1 ) {
        // trails[ t1_left_connect_id ] = trails[ t1_right_connect_id ];
        mergeTrails( t1_left_connect_id, t1_right_connect_id);
        t1_left_connect_id = t1_right_connect_id;
    }
    
    
    // merge t2
    if(t2_top_connect_id != t2_right_connect_id && t2_top_connect_id != -1 && t2_right_connect_id != -1 ) {
        // trails[ t2_right_connect_id ] = trails[ t2_top_connect_id ];
        mergeTrails( t2_right_connect_id, t2_top_connect_id );
        t2_right_connect_id = t2_top_connect_id;
    }
    if(t2_top_connect_id != t2_left_connect_id && t2_top_connect_id != -1 && t2_left_connect_id != -1 ) {
        // trails[ t2_left_connect_id ] = trails[ t2_top_connect_id ];
        mergeTrails( t2_left_connect_id  , t2_top_connect_id);
        t2_left_connect_id = t2_top_connect_id;
    }
    if(t2_top_connect_id != t2_bot_connect_id && t2_top_connect_id != -1 && t2_bot_connect_id != -1 ) {
        //  trails[ t2_bot_connect_id ] = trails[ t2_top_connect_id ];
        mergeTrails( t2_bot_connect_id, t2_top_connect_id   );
        t2_bot_connect_id = t2_top_connect_id;
    }
    
    if(t2_left_connect_id != t2_bot_connect_id && t2_left_connect_id != -1 && t2_bot_connect_id != -1 ) {
        // trails[ t2_bot_connect_id ] = trails[ t2_left_connect_id ];
        mergeTrails( t2_bot_connect_id, t2_left_connect_id   );
        t2_bot_connect_id = t2_left_connect_id;
    }
    if(t2_right_connect_id != t2_bot_connect_id && t2_right_connect_id != -1 && t2_bot_connect_id != -1 ) {
        // trails[ t2_bot_connect_id ] = trails[ t2_right_connect_id ];
        mergeTrails( t2_bot_connect_id, t2_right_connect_id  );
        t2_bot_connect_id = t2_right_connect_id;
    }
    
    if(t2_left_connect_id != t2_right_connect_id && t2_left_connect_id != -1 && t2_right_connect_id != -1 ) {
        //   trails[ t2_left_connect_id ] = trails[ t2_right_connect_id ];
        mergeTrails( t2_left_connect_id, t2_right_connect_id   );
        t2_left_connect_id = t2_right_connect_id;
    }
    
    
    // merge t3
    if(t3_top_connect_id != t3_right_connect_id && t3_top_connect_id != -1 && t3_right_connect_id != -1 ) {
        // trails[ t3_right_connect_id ] = trails[ t3_top_connect_id ];
        mergeTrails( t3_right_connect_id, t3_top_connect_id   );
        t3_right_connect_id = t3_top_connect_id;
    }
    if(t3_top_connect_id != t3_left_connect_id && t3_top_connect_id != -1 && t3_left_connect_id != -1 ) {
        //  trails[ t3_left_connect_id ] = trails[ t3_top_connect_id ];
        mergeTrails( t3_left_connect_id, t3_top_connect_id   );
        t3_left_connect_id = t3_top_connect_id;
    }
    if(t3_top_connect_id != t3_bot_connect_id && t3_top_connect_id != -1 && t3_bot_connect_id != -1 ) {
        //   trails[ t3_bot_connect_id ] = trails[ t3_top_connect_id ];
        mergeTrails( t3_bot_connect_id, t3_top_connect_id   );
        t3_bot_connect_id = t3_top_connect_id;
    }
    
    if(t3_left_connect_id != t3_bot_connect_id && t3_left_connect_id != -1 && t3_bot_connect_id != -1 ) {
        //  trails[ t3_bot_connect_id ] = trails[ t3_left_connect_id ];
        mergeTrails( t3_bot_connect_id, t3_left_connect_id   );
        t3_bot_connect_id = t3_left_connect_id;
    }
    if(t3_right_connect_id != t3_bot_connect_id && t3_right_connect_id != -1 && t3_bot_connect_id != -1 ) {
        // trails[ t3_bot_connect_id ] = trails[ t3_right_connect_id ];
        mergeTrails( t3_bot_connect_id, t3_right_connect_id   );
        t3_bot_connect_id = t3_right_connect_id;
    }
    
    if(t3_left_connect_id != t3_right_connect_id && t3_left_connect_id != -1 && t3_right_connect_id != -1 ) {
        // trails[ t3_left_connect_id ] = trails[ t3_right_connect_id ];
        mergeTrails( t3_left_connect_id, t3_right_connect_id  );
        t3_left_connect_id = t3_right_connect_id;
    }
    
    
    // merge t4
    if(t4_top_connect_id != t4_right_connect_id && t4_top_connect_id != -1 && t4_right_connect_id != -1 ) {
        //trails[ t4_right_connect_id ] = trails[ t4_top_connect_id ];
        mergeTrails( t4_right_connect_id, t4_top_connect_id   );
        t4_right_connect_id = t4_top_connect_id;
    }
    if(t4_top_connect_id != t4_left_connect_id && t4_top_connect_id != -1 && t4_left_connect_id != -1 ) {
        // trails[ t4_left_connect_id ] = trails[ t4_top_connect_id ];
        mergeTrails( t4_left_connect_id, t4_top_connect_id   );
        t4_left_connect_id = t4_top_connect_id;
    }
    if(t4_top_connect_id != t4_bot_connect_id && t4_top_connect_id != -1 && t4_bot_connect_id != -1 ) {
        // trails[ t4_bot_connect_id ] = trails[ t4_top_connect_id ];
        mergeTrails( t4_bot_connect_id, t4_top_connect_id   );
        t4_bot_connect_id = t4_top_connect_id;
    }
    
    if(t4_left_connect_id != t4_bot_connect_id && t4_left_connect_id != -1 && t4_bot_connect_id != -1 ) {
        //trails[ t4_bot_connect_id ] = trails[ t4_left_connect_id ];
        mergeTrails( t4_bot_connect_id, t4_left_connect_id   );
        t4_bot_connect_id = t4_left_connect_id;
    }
    if(t4_right_connect_id != t4_bot_connect_id && t4_right_connect_id != -1 && t4_bot_connect_id != -1 ) {
        //   trails[ t4_bot_connect_id ] = trails[ t4_right_connect_id ];
        mergeTrails( t4_bot_connect_id, t4_right_connect_id   );
        t4_bot_connect_id = t4_right_connect_id;
    }
    if(t4_left_connect_id != t4_right_connect_id && t4_left_connect_id != -1 && t4_right_connect_id != -1 ) {
        // trails[ t4_left_connect_id ] = trails[ t4_right_connect_id ];
        mergeTrails( t4_left_connect_id, t4_right_connect_id   );
        t4_left_connect_id = t4_right_connect_id;
    }
    
    
    // merge l1
    if(l1_top_connect_id != l1_right_connect_id && l1_top_connect_id != -1 && l1_right_connect_id != -1 ) {
        cout << "merging lake1 top and right connectors to 'new' lake " << endl;
        mergeLakes(l1_right_connect_id, l1_top_connect_id);
        l1_right_connect_id = l1_top_connect_id;
        // lakes[ l1_right_connect_id ] = lakes[ l1_top_connect_id ];
    }
    if(l1_top_connect_id != l1_left_connect_id && l1_top_connect_id != -1 && l1_left_connect_id != -1 ) {
        cout << "merging lake1 top and left connectors to 'new' lake " << endl;
        //lakes[ l1_left_connect_id ] = lakes[ l1_top_connect_id ];
        mergeLakes(l1_left_connect_id, l1_top_connect_id);
        l1_left_connect_id = l1_top_connect_id;
    }
    if(l1_top_connect_id != l1_bot_connect_id && l1_top_connect_id != -1 && l1_bot_connect_id != -1 ) {
        cout << "merging lake1 top and bot connectors to 'new' lake " << endl;
        //lakes[ l1_bot_connect_id ] = lakes[ l1_top_connect_id ];
        mergeLakes(l1_bot_connect_id, l1_top_connect_id);
        l1_bot_connect_id = l1_top_connect_id;
    }
    
    if(l1_left_connect_id != l1_bot_connect_id && l1_left_connect_id != -1 && l1_bot_connect_id != -1 ) {
        cout << "merging lake1 left and bot connectors to 'new' lake " << endl;
        // lakes[ l1_bot_connect_id ] = lakes[ l1_left_connect_id ];
        mergeLakes(l1_bot_connect_id, l1_left_connect_id);
        l1_bot_connect_id = l1_left_connect_id;
    }
    if(l1_right_connect_id != l1_bot_connect_id && l1_right_connect_id != -1 && l1_bot_connect_id != -1 ) {
        cout << "merging lake1 right and bot connectors to 'new' lake " << endl;
        //lakes[ l1_bot_connect_id ] = lakes[ l1_right_connect_id ];
        mergeLakes(l1_bot_connect_id, l1_right_connect_id);
        l1_bot_connect_id = l1_right_connect_id;
    }
    
    if(l1_left_connect_id != l1_right_connect_id && l1_left_connect_id != -1 && l1_right_connect_id != -1 ) {
        cout << "merging lake1 left and right connectors to 'new' lake " << endl;
        //lakes[ l1_left_connect_id ] = lakes[ l1_right_connect_id ];
        mergeLakes(l1_left_connect_id, l1_right_connect_id);
        l1_left_connect_id = l1_right_connect_id;
    }
    
    
    // merge l2
    if(l2_top_connect_id != l2_right_connect_id && l2_top_connect_id != -1 && l2_right_connect_id != -1 ) {
        cout << "merging lake1 top and right connectors to 'new' lake " << endl;
        //  lakes[ l2_right_connect_id ] = lakes[ l2_top_connect_id ];
        mergeLakes( l2_right_connect_id, l2_top_connect_id);
        l2_right_connect_id = l2_top_connect_id;
    }
    if(l2_top_connect_id != l2_left_connect_id && l2_top_connect_id != -1 && l2_left_connect_id != -1 ) {
        cout << "merging lake1 top and left connectors to 'new' lake " << endl;
        //  lakes[ l2_left_connect_id ] = lakes[ l2_top_connect_id ];
        mergeLakes(l2_left_connect_id, l2_top_connect_id);
        l2_left_connect_id = l2_top_connect_id;
    }
    if(l2_top_connect_id != l2_bot_connect_id && l2_top_connect_id != -1 && l2_bot_connect_id != -1 ) {
        cout << "merging lake1 top and bot connectors to 'new' lake " << endl;
        //  lakes[ l2_bot_connect_id ] = lakes[ l2_top_connect_id ];
        mergeLakes(l2_bot_connect_id, l2_top_connect_id);
        l2_bot_connect_id = l2_top_connect_id;
    }
    
    if(l2_left_connect_id != l2_bot_connect_id && l2_left_connect_id != -1 && l2_bot_connect_id != -1 ) {
        cout << "merging lake1 left and bot connectors to 'new' lake " << endl;
        // lakes[ l2_bot_connect_id ] = lakes[ l2_left_connect_id ];
        mergeLakes(l2_bot_connect_id, l2_left_connect_id);
        l2_bot_connect_id = l2_left_connect_id;
    }
    if(l2_right_connect_id != l2_bot_connect_id && l2_right_connect_id != -1 && l2_bot_connect_id != -1 ) {
        cout << "merging lake1 right and bot connectors to 'new' lake " << endl;
        //  lakes[ l2_bot_connect_id ] = lakes[ l2_right_connect_id ];
        mergeLakes(l2_bot_connect_id, l2_right_connect_id);
        l2_bot_connect_id = l2_right_connect_id;
    }
    
    if(l2_left_connect_id != l2_right_connect_id && l2_left_connect_id != -1 && l2_right_connect_id != -1 ) {
        cout << "merging lake1 left and right connectors to 'new' lake " << endl;
        // lakes[ l2_left_connect_id ] = lakes[ l2_right_connect_id ];
        mergeLakes(l2_left_connect_id, l2_right_connect_id);
        l2_left_connect_id = l2_right_connect_id;
    }
    
    // merge j1
    if(j1_top_connect_id != j1_right_connect_id && j1_top_connect_id != -1 && j1_right_connect_id != -1 ) {
       // jungles[ j1_right_connect_id ] = jungles[ j1_top_connect_id ];
        mergeJungles( j1_right_connect_id, j1_top_connect_id   );
        j1_right_connect_id = j1_top_connect_id;
    }
    if(j1_top_connect_id != j1_left_connect_id && j1_top_connect_id != -1 && j1_left_connect_id != -1 ) {
       // jungles[ j1_left_connect_id ] = jungles[ j1_top_connect_id ];
        mergeJungles( j1_left_connect_id, j1_top_connect_id   );
        j1_left_connect_id = j1_top_connect_id;
    }
    if(j1_top_connect_id != j1_bot_connect_id && j1_top_connect_id != -1 && j1_bot_connect_id != -1 ) {
      //  jungles[ j1_bot_connect_id ] = jungles[ j1_top_connect_id ];
        mergeJungles( j1_bot_connect_id, j1_top_connect_id);
        j1_bot_connect_id = j1_top_connect_id;
    }
    
    if(j1_left_connect_id != j1_bot_connect_id && j1_left_connect_id != -1 && j1_bot_connect_id != -1 ) {
        //jungles[ j1_bot_connect_id ] = jungles[ j1_left_connect_id ];
        mergeJungles( j1_bot_connect_id, j1_left_connect_id   );
        j1_bot_connect_id = j1_left_connect_id;
    }
    if(j1_right_connect_id != j1_bot_connect_id && j1_right_connect_id != -1 && j1_bot_connect_id != -1 ) {
        ///jungles[ j1_bot_connect_id ] = jungles[ j1_right_connect_id ];
        mergeJungles( j1_bot_connect_id, j1_right_connect_id    );
        j1_bot_connect_id = j1_right_connect_id;
    }
    
    if(j1_left_connect_id != j1_right_connect_id && j1_left_connect_id != -1 && j1_right_connect_id != -1 ) {
       // jungles[ j1_left_connect_id ] = jungles[ j1_right_connect_id ];
        mergeJungles( j1_left_connect_id, j1_right_connect_id   );
        j1_left_connect_id = j1_right_connect_id;
    }
    
    // merge j2
    if(j2_top_connect_id != j2_right_connect_id && j2_top_connect_id != -1 && j2_right_connect_id != -1 ) {
       // jungles[ j2_right_connect_id ] = jungles[ j2_top_connect_id ];
        mergeJungles( j2_right_connect_id, j2_top_connect_id   );
        j2_right_connect_id = j2_top_connect_id;
    }
    if(j2_top_connect_id != j2_left_connect_id && j2_top_connect_id != -1 && j2_left_connect_id != -1 ) {
      //  jungles[ j2_left_connect_id ] = jungles[ j2_top_connect_id ];
        mergeJungles( j2_left_connect_id, j2_top_connect_id   );
        j2_left_connect_id = j2_top_connect_id;
    }
    if(j2_top_connect_id != j2_bot_connect_id && j2_top_connect_id != -1 && j2_bot_connect_id != -1 ) {
       // jungles[ j2_bot_connect_id ] = jungles[ j2_top_connect_id ];
        mergeJungles( j2_bot_connect_id, j2_top_connect_id   );
        j2_bot_connect_id = j2_top_connect_id;
    }
    
    if(j2_left_connect_id != j2_bot_connect_id && j2_left_connect_id != -1 && j2_bot_connect_id != -1 ) {
      //  jungles[ j2_bot_connect_id ] = jungles[ j2_left_connect_id ];
        mergeJungles( j2_bot_connect_id, j2_left_connect_id );
        j2_bot_connect_id = j2_left_connect_id;
    }
    if(j2_right_connect_id != j2_bot_connect_id && j2_right_connect_id != -1 && j2_bot_connect_id != -1 ) {
        //jungles[ j2_bot_connect_id ] = jungles[ j2_right_connect_id ];
        mergeJungles( j2_bot_connect_id, j2_right_connect_id   );
        j2_bot_connect_id = j2_right_connect_id;
    }
    
    if(j2_left_connect_id != j2_right_connect_id && j2_left_connect_id != -1 && j2_right_connect_id != -1 ) {
       // jungles[ j2_left_connect_id ] = jungles[ j2_right_connect_id ];
        mergeJungles( j2_left_connect_id , j2_right_connect_id   );
        j2_left_connect_id = j2_right_connect_id;
    }
    
    
    // merge j3
    if(j3_top_connect_id != j3_right_connect_id && j3_top_connect_id != -1 && j3_right_connect_id != -1 ) {
       // jungles[ j3_right_connect_id ] = jungles[ j3_top_connect_id ];
        mergeJungles( j3_right_connect_id, j3_top_connect_id   );
        j3_right_connect_id = j3_top_connect_id;
    }
    if(j3_top_connect_id != j3_left_connect_id && j3_top_connect_id != -1 && j3_left_connect_id != -1 ) {
       // jungles[ j3_left_connect_id ] = jungles[ j3_top_connect_id ];
        mergeJungles( j3_left_connect_id, j3_top_connect_id   );
        j3_left_connect_id = j3_top_connect_id;
    }
    if(j3_top_connect_id != j3_bot_connect_id && j3_top_connect_id != -1 && j3_bot_connect_id != -1 ) {
       // jungles[ j3_bot_connect_id ] = jungles[ j3_top_connect_id ];
        mergeJungles( j3_bot_connect_id, j3_top_connect_id   );
        j3_bot_connect_id = j3_top_connect_id;
    }
    
    if(j3_left_connect_id != j3_bot_connect_id && j3_left_connect_id != -1 && j3_bot_connect_id != -1 ) {
       // jungles[ j3_bot_connect_id ] = jungles[ j3_left_connect_id ];
        mergeJungles( j3_bot_connect_id, j3_left_connect_id   );
        j3_bot_connect_id = j3_left_connect_id;
    }
    if(j3_right_connect_id != j3_bot_connect_id && j3_right_connect_id != -1 && j3_bot_connect_id != -1 ) {
       // jungles[ j3_bot_connect_id ] = jungles[ j3_right_connect_id ];
        mergeJungles( j3_bot_connect_id, j3_right_connect_id   );
        j3_bot_connect_id = j3_right_connect_id;
    }
    
    if(j3_left_connect_id != j3_right_connect_id && j3_left_connect_id != -1 && j3_right_connect_id != -1 ) {
       // jungles[ j3_left_connect_id ] = jungles[ j3_right_connect_id ];
        mergeJungles( j3_left_connect_id, j3_right_connect_id   );
        j3_left_connect_id = j3_right_connect_id;
    }
    
    
    // merge j4
    if(j4_top_connect_id != j4_right_connect_id && j4_top_connect_id != -1 && j4_right_connect_id != -1 ) {
       // jungles[ j4_right_connect_id ] = jungles[ j4_top_connect_id ];
        mergeJungles( j4_right_connect_id, j4_top_connect_id   );
        j4_right_connect_id = j4_top_connect_id;
    }
    if(j4_top_connect_id != j4_left_connect_id && j4_top_connect_id != -1 && j4_left_connect_id != -1 ) {
       // jungles[ j4_left_connect_id ] = jungles[ j4_top_connect_id ];
        mergeJungles( j4_left_connect_id, j4_top_connect_id   );
        j4_left_connect_id = j4_top_connect_id;
    }
    if(j4_top_connect_id != j4_bot_connect_id && j4_top_connect_id != -1 && j4_bot_connect_id != -1 ) {
       // jungles[ j4_bot_connect_id ] = jungles[ j4_top_connect_id ];
        mergeJungles( j4_bot_connect_id, j4_top_connect_id   );
        j4_bot_connect_id = j4_top_connect_id;
    }
    
    if(j4_left_connect_id != j4_bot_connect_id && j4_left_connect_id != -1 && j4_bot_connect_id != -1 ) {
       // jungles[ j4_bot_connect_id ] = jungles[ j4_left_connect_id ];
        mergeJungles( j4_bot_connect_id, j4_left_connect_id   );
        j4_bot_connect_id = j4_left_connect_id;
    }
    if(j4_right_connect_id != j4_bot_connect_id && j4_right_connect_id != -1 && j4_bot_connect_id != -1 ) {
       // jungles[ j4_bot_connect_id ] = jungles[ j4_right_connect_id ];
        mergeJungles( j4_bot_connect_id, j4_right_connect_id   );
        j4_bot_connect_id = j4_right_connect_id;
    }
    if(j4_left_connect_id != j4_right_connect_id && j4_left_connect_id != -1 && j4_right_connect_id != -1 ) {
       // jungles[ j4_left_connect_id ] = jungles[ j4_right_connect_id ];
        mergeJungles( j4_left_connect_id, j4_right_connect_id   );
        j4_left_connect_id = j4_right_connect_id;
    }
    
}

void Board::incrementEdges(int i, int j, Card * card) {

    // top edge
    if(card->topEdge->getType() == 'J') {                           // jungle top edge connects to nothing
        if(i > 0 && board[i-1][j].botEdge->getType() != 'J') {
            if      (card->topEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
        }
        else if(i > 0 && board[i-1][j].botEdge->getType() == 'J') {
            if      (card->topEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
        }
    }
    
    // bot edge
    if(card->botEdge->getType() == 'J') {                           // jungle top edge connects to nothing
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() != 'J') {
            if      (card->botEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
        }
        else if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'J') {
            if      (card->botEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
        }
    }
    //right edge
    if(card->rightEdge->getType() == 'J') {                           // jungle top edge connects to nothing
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() != 'J') {
            if      (card->rightEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
        }
        else if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'J') {
            if      (card->rightEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
        }
    }
    //left edge
    if(card->leftEdge->getType() == 'J') {                           // jungle top edge connects to nothing
        if(j > 0 && board[i][j-1].rightEdge->getType() != 'J') {
            if      (card->leftEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
        }
        else if(j > 0 && board[i][j-1].rightEdge->getType() == 'J') {
            if      (card->leftEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
        }
    }
    // top edge
    if(card->topEdge->getType() == 'L') {                           // lake top edge connects to nothing
        if(i > 0 && board[i-1][j].botEdge->getType() != 'L') {
            if      (card->topEdge->l1 == card->l1) {
                card->l1->edgeConnects++;
            }
            else if (card->topEdge->l1 == card->l2) {
                card->l2->edgeConnects++;
            }
        }
        else if(i > 0 && board[i-1][j].botEdge->getType() == 'L') {
            if      (card->topEdge->l1 == card->l1) {
                card->l1->edgeConnects--;
            }
            else if (card->topEdge->l1 == card->l2) {
                card->l2->edgeConnects--;
            }
        }
    }
    
    // bot edge
    if(card->botEdge->getType() == 'L') {                           // lake top edge connects to nothing
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() != 'L') {
            if      (card->botEdge->l1 == card->l1) {
                card->l1->edgeConnects++;
            }
            else if (card->botEdge->l1 == card->l2) {
                card->l2->edgeConnects++;
            }
        }
        else if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'L') {
            if      (card->botEdge->l1 == card->l1) {
                card->l1->edgeConnects--;
            }
            else if (card->botEdge->l1 == card->l2) {
                card->l2->edgeConnects--;
            }
        }
    }
    //right edge
    if(card->rightEdge->getType() == 'L') {                           // lake top edge connects to nothing
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() != 'L') {
            if      (card->rightEdge->l1 == card->l1) {
                card->l1->edgeConnects++;
            }
            else if (card->rightEdge->l1 == card->l2) {
                card->l2->edgeConnects++;
            }
        }
        else if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'L') {
            if      (card->rightEdge->l1 == card->l1) {
                card->l1->edgeConnects--;
            }
            else if (card->rightEdge->l1 == card->l2) {
                card->l2->edgeConnects--;
            }
        }
    }
    //left edge
    if(card->leftEdge->getType() == 'L') {                           // lake top edge connects to nothing
        if(j > 0 && board[i][j-1].rightEdge->getType() != 'L') {
            if      (card->leftEdge->l1 == card->l1) {
                card->l1->edgeConnects++;
            }
            else if (card->leftEdge->l1 == card->l2) {
                card->l2->edgeConnects++;
            }
        }
        else if(j > 0 && board[i][j-1].rightEdge->getType() == 'L') {
            if      (card->leftEdge->l1 == card->l1) {
                card->l1->edgeConnects--;
            }
            else if (card->leftEdge->l1 == card->l2) {
                card->l2->edgeConnects--;
            }
        }
    }
    // top edge
    if(card->topEdge->getType() == 'T') {                           // lake top edge connects to nothing
        if(i > 0 && board[i-1][j].botEdge->getType() != 'T') {
            if      (card->topEdge->t1 == card->t1) {
                card->t1->edgeConnects++;
            }
            else if (card->topEdge->t1 == card->t2) {
                card->t2->edgeConnects++;
            }
            else if (card->topEdge->t1 == card->t3) {
                card->t3->edgeConnects++;
            }
            else if (card->topEdge->t1 == card->t4) {
                card->t4->edgeConnects++;
            }
            
            if      (card->topEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->topEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
            
            if      (card->topEdge->j2 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->topEdge->j2 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->topEdge->j2 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->topEdge->j2 == card->j4) {
                card->j4->edgeConnects++;
            }
            
        }
        
        
        
        
        
        
        
        else if(i > 0 && board[i-1][j].botEdge->getType() == 'T') {
            
            
            if      (card->topEdge->t1 == card->t1) {
                card->t1->edgeConnects--;
            }
            else if (card->topEdge->t1 == card->t2) {
                card->t2->edgeConnects--;
            }
            else if (card->topEdge->t1 == card->t3) {
                card->t3->edgeConnects--;
            }
            else if (card->topEdge->t1 == card->t4) {
                card->t4->edgeConnects--;
            }
                
            
            if      (card->topEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->topEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
            
            if      (card->topEdge->j2 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->topEdge->j2 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->topEdge->j2 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->topEdge->j2 == card->j4) {
                card->j4->edgeConnects--;
            }
            
        }
        
        
        
        
    }
    
    // bot edge
    if(card->botEdge->getType() == 'T') {                           // lake top edge connects to nothing
        if(i < ROWS - 1 && board[i+1][j].topEdge->getType() != 'T') {
           
            
            
            
            if      (card->botEdge->t1 == card->t1) {
                card->t1->edgeConnects++;
            }
            else if (card->botEdge->t1 == card->t2) {
                card->t2->edgeConnects++;
            }
            else if (card->botEdge->t1 == card->t3) {
                card->t3->edgeConnects++;
            }
            else if (card->botEdge->t1 == card->t4) {
                card->t4->edgeConnects++;
            }
            
            if      (card->botEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->botEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
            
            if      (card->botEdge->j2 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->botEdge->j2 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->botEdge->j2 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->botEdge->j2 == card->j4) {
                card->j4->edgeConnects++;
            }
            
            
            
            
        }
        else if(i < ROWS - 1 && board[i+1][j].topEdge->getType() == 'T') {
         
            
            if      (card->botEdge->t1 == card->t1) {
                card->t1->edgeConnects--;
            }
            else if (card->botEdge->t1 == card->t2) {
                card->t2->edgeConnects--;
            }
            else if (card->botEdge->t1 == card->t3) {
                card->t3->edgeConnects--;
            }
            else if (card->botEdge->t1 == card->t4) {
                card->t4->edgeConnects--;
            }
            
                
            
            if      (card->botEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->botEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
            
            if      (card->botEdge->j2 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->botEdge->j2 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->botEdge->j2 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->botEdge->j2 == card->j4) {
                card->j4->edgeConnects--;
            }
            
        }
    }
    //right edge
    if(card->rightEdge->getType() == 'T') {                           // lake top edge connects to nothing
        if(j < COLS - 1 && board[i][j+1].leftEdge->getType() != 'T') {
            if      (card->rightEdge->t1 == card->t1) {
                card->t1->edgeConnects++;
            }
            else if (card->rightEdge->t1 == card->t2) {
                card->t2->edgeConnects++;
            }
            else if (card->rightEdge->t1 == card->t3) {
                card->t3->edgeConnects++;
            }
            else if (card->rightEdge->t1 == card->t4) {
                card->t4->edgeConnects++;
            }
            
            if      (card->rightEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->rightEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
            
            if      (card->rightEdge->j2 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->rightEdge->j2 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->rightEdge->j2 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->rightEdge->j2 == card->j4) {
                card->j4->edgeConnects++;
            }
            
        }
        else if(j < COLS - 1 && board[i][j+1].leftEdge->getType() == 'T') {
          
          
            if      (card->rightEdge->t1 == card->t1) {
                card->t1->edgeConnects--;
            }
            else if (card->rightEdge->t1 == card->t2) {
                card->t2->edgeConnects--;
            }
            else if (card->rightEdge->t1 == card->t3) {
                card->t3->edgeConnects--;
            }
            else if (card->rightEdge->t1 == card->t4) {
                card->t4->edgeConnects--;
            }
            
            
            
            if      (card->rightEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->rightEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
            
            if      (card->rightEdge->j2 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->rightEdge->j2 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->rightEdge->j2 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->rightEdge->j2 == card->j4) {
                card->j4->edgeConnects--;
            }
            
        }
    }
    //left edge
    if(card->leftEdge->getType() == 'T') {                           // lake top edge connects to nothing
        if(j > 0 && board[i][j-1].rightEdge->getType() != 'T') {
            if      (card->leftEdge->t1 == card->t1) {
                card->t1->edgeConnects++;
            }
            else if (card->leftEdge->t1 == card->t2) {
                card->t2->edgeConnects++;
            }
            else if (card->leftEdge->t1 == card->t3) {
                card->t3->edgeConnects++;
            }
            else if (card->leftEdge->t1 == card->t4) {
                card->t4->edgeConnects++;
            }
            
            if      (card->leftEdge->j1 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->leftEdge->j1 == card->j4) {
                card->j4->edgeConnects++;
            }
            
            if      (card->leftEdge->j2 == card->j1) {
                card->j1->edgeConnects++;
            }
            else if (card->leftEdge->j2 == card->j2) {
                card->j2->edgeConnects++;
            }
            else if (card->leftEdge->j2 == card->j3) {
                card->j3->edgeConnects++;
            }
            else if (card->leftEdge->j2 == card->j4) {
                card->j4->edgeConnects++;
            }
            
        }
        else if(j > 0 && board[i][j-1].rightEdge->getType() == 'T') {
            
            
            if      (card->leftEdge->t1 == card->t1) {
                card->t1->edgeConnects--;
            }
            else if (card->leftEdge->t1 == card->t2) {
                card->t2->edgeConnects--;
            }
            else if (card->leftEdge->t1 == card->t3) {
                card->t3->edgeConnects--;
            }
            else if (card->leftEdge->t1 == card->t4) {
                card->t4->edgeConnects--;
            }
            
            if      (card->leftEdge->j1 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->leftEdge->j1 == card->j4) {
                card->j4->edgeConnects--;
            }
            
            if      (card->leftEdge->j2 == card->j1) {
                card->j1->edgeConnects--;
            }
            else if (card->leftEdge->j2 == card->j2) {
                card->j2->edgeConnects--;
            }
            else if (card->leftEdge->j2 == card->j3) {
                card->j3->edgeConnects--;
            }
            else if (card->leftEdge->j2 == card->j4) {
                card->j4->edgeConnects--;
            }
            
        }
    }
    
    
    
    // increment prey count
    
    if(card->getId() == 15 || card->getId() == 17 || card->getId() == 19 || card->getId() == 22 || card->getId() == 24 || card->getId() == 26) {
        
        if(card->t1 != NULL) {
            card->t1->preyCount++;
        }
        if(card->t2 != NULL) {
            card->t2->preyCount++;
        }
        if(card->t3 != NULL) {
            card->t3->preyCount++;
        }
        if(card->t4 != NULL) {
            card->t4->preyCount++;
        }
    }
    else if(card->getId() == 27) {
        if(card->t1 != NULL) {
            card->t1->preyCount--;
        }
        if(card->t2 != NULL) {
            card->t2->preyCount--;
        }
        if(card->t3 != NULL) {
            card->t3->preyCount--;
        }
        if(card->t4 != NULL) {
            card->t4->preyCount--;
        }
    }
    
    
    
    if(card->getId() == 15 || card->getId() == 22)  {
        if(card->l1 != NULL && !card->l1->hasBoar) {
            card->l1->preyCount++;
        }
        if(card->l2 != NULL && !card->l2->hasBoar) {
            card->l2->preyCount++;
        }
    }
    else if(card->getId() == 17 || card->getId() == 24)  {
        if(card->l1 != NULL && !card->l1->hasBuffalo) {
            card->l1->preyCount++;
        }
        if(card->l2 != NULL && !card->l1->hasBuffalo) {
            card->l2->preyCount++;
        }
    }
    else if(card->getId() == 19 || card->getId() == 26)  {
        if(card->l1 != NULL && !card->l1->hasDeer) {
            card->l1->preyCount++;
        }
        if(card->l2 != NULL && !card->l1->hasDeer) {
            card->l2->preyCount++;
        }
    }
    else if(card->getId() == 27) {
        if(card->l1 != NULL) {
            card->l1->preyCount--;
        }
        if(card->l2 != NULL) {
            card->l2->preyCount--;
        }
    }
    
    
    if(card->t1 != NULL) {
        card->t1->numTiles++;
    }
    if(card->t2 != NULL) {
        card->t2->numTiles++;
    }
    if(card->t3 != NULL) {
        card->t3->numTiles++;
    }
    if(card->t4 != NULL) {
        card->t4->numTiles++;
    }
    if(card->j1 != NULL) {
        card->j1->numTiles++;
    }
    if(card->j2 != NULL) {
        card->j2->numTiles++;
    }
    if(card->j3 != NULL) {
        card->j3->numTiles++;
    }
    if(card->j4 != NULL) {
        card->j4->numTiles++;
    }
    if(card->l1 != NULL) {
        card->l1->numTiles++;
    }
    if(card->l2 != NULL) {
        card->l2->numTiles++;
    }

    
}


void Board::mergeLakes(int l1_id, int l2_id) {
    
    int region1_tileCount = lakes[ l1_id ].numTiles;
    int region2_tileCount = lakes[ l2_id ].numTiles;
    
    int region1_edgeCount = lakes[ l1_id ].edgeConnects;
    int region2_edgeCount = lakes[ l2_id ].edgeConnects;
    
    int p1_region1_tigerCount = lakes[ l1_id ].num_tigers_p1;
    int p2_region1_tigerCount = lakes[ l1_id ].num_tigers_p2;
    
    int p1_region2_tigerCount = lakes[ l2_id ].num_tigers_p1;
    int p2_region2_tigerCount = lakes[ l2_id ].num_tigers_p2;

    int uniquePrey = 0;
    if( lakes[ l1_id ].hasBoar || lakes[ l2_id ].hasBoar ) {
        uniquePrey++;
    }
    if( lakes[ l1_id ].hasBuffalo || lakes[ l2_id ].hasBuffalo) {
        uniquePrey++;
    }
    if( lakes[ l1_id ].hasDeer || lakes[ l2_id ].hasDeer) {
        uniquePrey++;
    }
    
    lakes[ l2_id ].num_tigers_p1 = p1_region1_tigerCount + p1_region2_tigerCount;
    lakes[ l2_id ].num_tigers_p2 = p2_region1_tigerCount + p2_region2_tigerCount;
    lakes[ l2_id ].preyCount = uniquePrey;
    lakes[ l2_id ].numTiles = region1_tileCount + region2_tileCount;
    lakes[ l2_id ].edgeConnects = region1_edgeCount + region2_edgeCount;

    lakes[ l1_id ].clearState();
}

void Board::mergeTrails(int t1_id, int t2_id) {
    
    int region1_tileCount = trails[ t1_id ].numTiles;
    int region2_tileCount = trails[ t2_id ].numTiles;
    
    int region1_edgeCount = trails[ t1_id ].edgeConnects;
    int region2_edgeCount = trails[ t2_id ].edgeConnects;

    int p1_region1_tigerCount = trails[ t1_id ].num_tigers_p1;
    int p2_region1_tigerCount = trails[ t1_id ].num_tigers_p2;
    
    int p1_region2_tigerCount = trails[ t2_id ].num_tigers_p1;
    int p2_region2_tigerCount = trails[ t2_id ].num_tigers_p2;
    
    int region1_preyCount = trails[ t1_id ].preyCount;
    int region2_preyCount = trails[ t2_id ].preyCount;
    
    trails[ t2_id ].num_tigers_p1 = p1_region1_tigerCount + p1_region2_tigerCount;
    trails[ t2_id ].num_tigers_p2 = p2_region1_tigerCount + p2_region2_tigerCount;
    trails[ t2_id ].preyCount = region1_preyCount + region2_preyCount;
    trails[ t2_id ].numTiles = region1_tileCount + region2_tileCount;
    trails[ t2_id ].edgeConnects = region1_edgeCount + region2_edgeCount;

    trails[ t1_id ].clearState();
}

void Board::mergeJungles(int j1_id, int j2_id) {
    
    int p1_region1_tigerCount = jungles[ j1_id ].num_tigers_p1;
    int p2_region1_tigerCount = jungles[ j1_id ].num_tigers_p2;
    
    int region1_edgeCount = jungles[ j1_id ].edgeConnects;
    int region2_edgeCount = jungles[ j2_id ].edgeConnects;
    
    int p1_region2_tigerCount = jungles[ j2_id ].num_tigers_p1;
    int p2_region2_tigerCount = jungles[ j2_id ].num_tigers_p2;
    
    jungles[ j2_id ].num_tigers_p1 = p1_region1_tigerCount + p1_region2_tigerCount;
    jungles[ j2_id ].num_tigers_p2 = p2_region1_tigerCount + p2_region2_tigerCount;
    
    jungles[ j1_id ].clearState();
}


void Board::scoreMove(Card * card, int playerID) {
    
    // score the move: Completable features completed during the game are scored when completed and any tigers placed
    //                 upon them are returned to their owners
    
    if(card->t1 != NULL && card->t1->edgeConnects == 0) {
        cout << "t1 complete" << endl;
        scoreTrail(card->t1, playerID);
    }
    if(card->t2 != NULL && card->t2->edgeConnects == 0) {
        cout << "t2 complete" << endl;
        scoreTrail(card->t2, playerID);
    }
    if(card->t3 != NULL && card->t3->edgeConnects == 0) {
        cout << "t3 complete" << endl;
        scoreTrail(card->t3, playerID);
    }
    if(card->t4 != NULL && card->t4->edgeConnects == 0) {
        cout << "t4 complete" << endl;
        scoreTrail(card->t4, playerID);
    }
    if(card->j1 != NULL && card->j1->edgeConnects == 0) {
        cout << "j1 complete" << endl;
        scoreJungle(card->j1, playerID);
    }
    if(card->j2 != NULL && card->j2->edgeConnects == 0) {
        cout << "j2 complete" << endl;
        scoreJungle(card->j2, playerID);
    }
    if(card->j3 != NULL && card->j3->edgeConnects == 0) {
        cout << "j3 complete" << endl;
        scoreJungle(card->j3, playerID);
    }
    if(card->j4 != NULL && card->j4->edgeConnects == 0) {
        cout << "j4 complete" << endl;
        scoreJungle(card->j4, playerID);
    }
    if(card->l1 != NULL && card->l1->edgeConnects == 0) {
        cout << "l1 complete" << endl;
        scoreLake(card->l1, playerID);
    }
    if(card->l2 != NULL && card->l2->edgeConnects == 0) {
        cout << "l2 complete" << endl;
        scoreLake(card->l2, playerID);
    }
}


void Board::scoreLake(Lake * l, int playerID) {
    int numPreyInLake = (l->preyCount < 0)?0:l->preyCount;
    int points = (l->numTiles * 2) * ( 1 + numPreyInLake );
    cout << "Player " << l->getOwner() << " gets " << points << "points for completing lake # " << l->getId() << endl;
    if( l->getOwner() == 0) {  // shared region
        p1_score += points;
        p2_score += points;
    }
    else if (l->getOwner() == 1) {
        p1_score += points;
    }
    else if (l->getOwner() == 2) {
        p2_score += points;
    }
}

void Board::scoreJungle(Jungle * j, int playerID) {
    
}

void Board::scoreTrail( Trail * t, int playerID) {
    int numPreyInJungle = (t->preyCount < 0)?0:t->preyCount;
    int points = t->numTiles + numPreyInJungle;
    cout << "Player " << t->getOwner() << " gets " << points << "points for completing trail # " << t->getId() << endl;
    if( t->getOwner() == 0) {  // shared region
        p1_score += points;
        p2_score += points;
    }
    else if (t->getOwner() == 1) {
        p1_score += points;
    }
    else if (t->getOwner() == 2) {
        p2_score += points;
    }
}

int Board::getScore(bool player) {
    if(player) {
        return p1_score;
    }
    else {
        return p2_score;
    }
}

void Board::markAdjacentLakes( Card * card ) {
    
    
    
    
    
    if(card->j1 != NULL) {          // mark adjacent lakes
        
    }
    else if (card->j2 != NULL) {
        
    }
    else if (card->j3 != NULL) {
        
    }
    else if (card->j4 != NULL) {
        
    }
    
}

void Board::endGameScoring() {  // score uncompleted regions
    
    
    for(int i = 0; i < 100; i++) {
        if(lakes[i].numTiles > 0 && lakes[i].edgeConnects != 0) {   // if uncomplete
            int numPreyInLake = (lakes[i].preyCount < 0)?0:lakes[i].preyCount;
            int points = (lakes[i].numTiles * 1) * ( 1 + numPreyInLake );
            cout << "Player " <<lakes[i].getOwner() << " gets " << points << "points for uncomplete lake # " << lakes[i].getId() << endl;
            if( lakes[i].getOwner() == 0) {  // shared region
                p1_score += points;
                p2_score += points;
            }
            else if (lakes[i].getOwner() == 1) {
                p1_score += points;
            }
            else if (lakes[i].getOwner() == 2) {
                p2_score += points;
            }
        }
    }
    for(int i = 0; i < 100; i++) {
        if(trails[i].numTiles > 0) {
            int numPreyInJungle = (trails[i].preyCount < 0)?0:trails[i].preyCount;
            int points = trails[i].numTiles + numPreyInJungle;
            cout << "Player " << trails[i].getOwner() << " gets " << points << "points for uncomplete trail # " << trails[i].getId() << endl;
            if( trails[i].getOwner() == 0) {  // shared region
                p1_score += points;
                p2_score += points;
            }
            else if (trails[i].getOwner() == 1) {
                p1_score += points;
            }
            else if (trails[i].getOwner() == 2) {
                p2_score += points;
            }
        }
    }
}

void Board::getBestMove() {
    
    
    
}
    
