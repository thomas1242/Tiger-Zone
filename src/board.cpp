#include "board.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Board::Board(Card * card) {                            // board constructor                          // board constructor
		
	board = new Card * [ROWS];              // board is initially all open space ( cards with id = -1 )
	for(int i = 0; i < ROWS; ++i) {
		board[i] = new Card[COLS];
	}
	
	numJungles = 0;
	numTrails = 0;
	numLakes = 0;
	
	jungles = new Jungle[100];
	trails = new Trail[100];
	lakes = new Lake[100];
	for(int i = 0; i < 100; i++) {
		trails[i].setId(i );
		lakes[i].setId(i);
		jungles[i].setId(i);
	}
	
	
	cout << "Put center card on new board" << endl;

	placeCard(ROWS/2, COLS/2, card, 0, 1, 0);        // place center card on the board
}


bool Board::placeCard(int i, int j, Card * card, int rotations, int playerID, int zone) {
	

	if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  // for GUI, if user clicks out of bounds
		return false;
	}
	
	while( rotations !=0) {
		card->rotate();                     // rotate card until it fits at the valid location
		rotations--;
	}
	
   // cout << "Placed card " << card->getId() << " at [" << i << ',' << j << ']' << endl;
   // cout << "Placed card " << card->getId() << " at [" << j - 5 << ',' << -(i - 5) << ']' << endl;
	
	cout << "\n\n---------------------------------------------------------------------\n" << endl;
	
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
	
	// merge l1
	if(l1_top_connect_id != l1_right_connect_id && l1_top_connect_id != -1 && l1_right_connect_id != -1 ) {
		cout << "merging lake1 top and right connectors to 'new' lake " << endl;
		lakes[ l1_right_connect_id ] = lakes[ l1_top_connect_id ];
	}
	if(l1_top_connect_id != l1_left_connect_id && l1_top_connect_id != -1 && l1_left_connect_id != -1 ) {
		cout << "merging lake1 top and left connectors to 'new' lake " << endl;
		lakes[ l1_left_connect_id ] = lakes[ l1_top_connect_id ];
	}
	if(l1_top_connect_id != l1_bot_connect_id && l1_top_connect_id != -1 && l1_bot_connect_id != -1 ) {
		cout << "merging lake1 top and bot connectors to 'new' lake " << endl;
		lakes[ l1_bot_connect_id ] = lakes[ l1_top_connect_id ];
	}
	
	if(l1_left_connect_id != l1_bot_connect_id && l1_left_connect_id != -1 && l1_bot_connect_id != -1 ) {
		cout << "merging lake1 left and bot connectors to 'new' lake " << endl;
		lakes[ l1_bot_connect_id ] = lakes[ l1_left_connect_id ];
	}
	if(l1_right_connect_id != l1_bot_connect_id && l1_right_connect_id != -1 && l1_bot_connect_id != -1 ) {
		cout << "merging lake1 right and bot connectors to 'new' lake " << endl;
		lakes[ l1_bot_connect_id ] = lakes[ l1_right_connect_id ];
	}
	
	if(l1_left_connect_id != l1_right_connect_id && l1_left_connect_id != -1 && l1_right_connect_id != -1 ) {
		cout << "merging lake1 left and right connectors to 'new' lake " << endl;
		lakes[ l1_left_connect_id ] = lakes[ l1_right_connect_id ];
	}
	
	// merge l2
	if(l2_top_connect_id != l2_right_connect_id && l2_top_connect_id != -1 && l2_right_connect_id != -1 ) {
		cout << "merging lake1 top and right connectors to 'new' lake " << endl;
		lakes[ l2_right_connect_id ] = lakes[ l2_top_connect_id ];
	}
	if(l2_top_connect_id != l2_left_connect_id && l2_top_connect_id != -1 && l2_left_connect_id != -1 ) {
		cout << "merging lake1 top and left connectors to 'new' lake " << endl;
		lakes[ l2_left_connect_id ] = lakes[ l2_top_connect_id ];
	}
	if(l2_top_connect_id != l2_bot_connect_id && l2_top_connect_id != -1 && l2_bot_connect_id != -1 ) {
		cout << "merging lake1 top and bot connectors to 'new' lake " << endl;
		lakes[ l2_bot_connect_id ] = lakes[ l2_top_connect_id ];
	}
	
	if(l2_left_connect_id != l2_bot_connect_id && l2_left_connect_id != -1 && l2_bot_connect_id != -1 ) {
		cout << "merging lake1 left and bot connectors to 'new' lake " << endl;
		lakes[ l2_bot_connect_id ] = lakes[ l2_left_connect_id ];
	}
	if(l2_right_connect_id != l2_bot_connect_id && l2_right_connect_id != -1 && l2_bot_connect_id != -1 ) {
		cout << "merging lake1 right and bot connectors to 'new' lake " << endl;
		lakes[ l2_bot_connect_id ] = lakes[ l2_right_connect_id ];
	}
	
	if(l2_left_connect_id != l2_right_connect_id && l2_left_connect_id != -1 && l2_right_connect_id != -1 ) {
		cout << "merging lake1 left and right connectors to 'new' lake " << endl;
		lakes[ l2_left_connect_id ] = lakes[ l2_right_connect_id ];
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

	
	// merge t1
	if(t1_top_connect_id != t1_right_connect_id && t1_top_connect_id != -1 && t1_right_connect_id != -1 ) {
		trails[ t1_right_connect_id ] = trails[ t1_top_connect_id ];
	}
	if(t1_top_connect_id != t1_left_connect_id && t1_top_connect_id != -1 && t1_left_connect_id != -1 ) {
		trails[ t1_left_connect_id ] = trails[ t1_top_connect_id ];
	}
	if(t1_top_connect_id != t1_bot_connect_id && t1_top_connect_id != -1 && t1_bot_connect_id != -1 ) {
		trails[ t1_bot_connect_id ] = trails[ t1_top_connect_id ];
	}
	
	if(t1_left_connect_id != t1_bot_connect_id && t1_left_connect_id != -1 && t1_bot_connect_id != -1 ) {
		trails[ t1_bot_connect_id ] = trails[ t1_left_connect_id ];
	}
	if(t1_right_connect_id != t1_bot_connect_id && t1_right_connect_id != -1 && t1_bot_connect_id != -1 ) {
		trails[ t1_bot_connect_id ] = trails[ t1_right_connect_id ];
	}
	
	if(t1_left_connect_id != t1_right_connect_id && t1_left_connect_id != -1 && t1_right_connect_id != -1 ) {
		trails[ t1_left_connect_id ] = trails[ t1_right_connect_id ];
	}
	
	
	// merge t2
	if(t2_top_connect_id != t2_right_connect_id && t2_top_connect_id != -1 && t2_right_connect_id != -1 ) {
		trails[ t2_right_connect_id ] = trails[ t2_top_connect_id ];
	}
	if(t2_top_connect_id != t2_left_connect_id && t2_top_connect_id != -1 && t2_left_connect_id != -1 ) {
		trails[ t2_left_connect_id ] = trails[ t2_top_connect_id ];
	}
	if(t2_top_connect_id != t2_bot_connect_id && t2_top_connect_id != -1 && t2_bot_connect_id != -1 ) {
		trails[ t2_bot_connect_id ] = trails[ t2_top_connect_id ];
	}
	
	if(t2_left_connect_id != t2_bot_connect_id && t2_left_connect_id != -1 && t2_bot_connect_id != -1 ) {
		trails[ t2_bot_connect_id ] = trails[ t2_left_connect_id ];
	}
	if(t2_right_connect_id != t2_bot_connect_id && t2_right_connect_id != -1 && t2_bot_connect_id != -1 ) {
		trails[ t2_bot_connect_id ] = trails[ t2_right_connect_id ];
	}
	
	if(t2_left_connect_id != t2_right_connect_id && t2_left_connect_id != -1 && t2_right_connect_id != -1 ) {
		trails[ t2_left_connect_id ] = trails[ t2_right_connect_id ];
	}
	
	
	// merge t3
	if(t3_top_connect_id != t3_right_connect_id && t3_top_connect_id != -1 && t3_right_connect_id != -1 ) {
		trails[ t3_right_connect_id ] = trails[ t3_top_connect_id ];
	}
	if(t3_top_connect_id != t3_left_connect_id && t3_top_connect_id != -1 && t3_left_connect_id != -1 ) {
		trails[ t3_left_connect_id ] = trails[ t3_top_connect_id ];
	}
	if(t3_top_connect_id != t3_bot_connect_id && t3_top_connect_id != -1 && t3_bot_connect_id != -1 ) {
		trails[ t3_bot_connect_id ] = trails[ t3_top_connect_id ];
	}
	
	if(t3_left_connect_id != t3_bot_connect_id && t3_left_connect_id != -1 && t3_bot_connect_id != -1 ) {
		trails[ t3_bot_connect_id ] = trails[ t3_left_connect_id ];
	}
	if(t3_right_connect_id != t3_bot_connect_id && t3_right_connect_id != -1 && t3_bot_connect_id != -1 ) {
		trails[ t3_bot_connect_id ] = trails[ t3_right_connect_id ];
	}
	
	if(t3_left_connect_id != t3_right_connect_id && t3_left_connect_id != -1 && t3_right_connect_id != -1 ) {
		trails[ t3_left_connect_id ] = trails[ t3_right_connect_id ];
	}
	
	
	// merge t4
	if(t4_top_connect_id != t4_right_connect_id && t4_top_connect_id != -1 && t4_right_connect_id != -1 ) {
		trails[ t4_right_connect_id ] = trails[ t4_top_connect_id ];
	}
	if(t4_top_connect_id != t4_left_connect_id && t4_top_connect_id != -1 && t4_left_connect_id != -1 ) {
		trails[ t4_left_connect_id ] = trails[ t4_top_connect_id ];
	}
	if(t4_top_connect_id != t4_bot_connect_id && t4_top_connect_id != -1 && t4_bot_connect_id != -1 ) {
		trails[ t4_bot_connect_id ] = trails[ t4_top_connect_id ];
	}
	
	if(t4_left_connect_id != t4_bot_connect_id && t4_left_connect_id != -1 && t4_bot_connect_id != -1 ) {
		trails[ t4_bot_connect_id ] = trails[ t4_left_connect_id ];
	}
	if(t4_right_connect_id != t4_bot_connect_id && t4_right_connect_id != -1 && t4_bot_connect_id != -1 ) {
		trails[ t4_bot_connect_id ] = trails[ t4_right_connect_id ];
	}
	if(t4_left_connect_id != t4_right_connect_id && t4_left_connect_id != -1 && t4_right_connect_id != -1 ) {
		trails[ t4_left_connect_id ] = trails[ t4_right_connect_id ];
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

	
	
	
	// merge j1
	if(j1_top_connect_id != j1_right_connect_id && j1_top_connect_id != -1 && j1_right_connect_id != -1 ) {
		jungles[ j1_right_connect_id ] = jungles[ j1_top_connect_id ];
	}
	if(j1_top_connect_id != j1_left_connect_id && j1_top_connect_id != -1 && j1_left_connect_id != -1 ) {
		jungles[ j1_left_connect_id ] = jungles[ j1_top_connect_id ];
	}
	if(j1_top_connect_id != j1_bot_connect_id && j1_top_connect_id != -1 && j1_bot_connect_id != -1 ) {
		jungles[ j1_bot_connect_id ] = jungles[ j1_top_connect_id ];
	}
	
	if(j1_left_connect_id != j1_bot_connect_id && j1_left_connect_id != -1 && j1_bot_connect_id != -1 ) {
		jungles[ j1_bot_connect_id ] = jungles[ j1_left_connect_id ];
	}
	if(j1_right_connect_id != j1_bot_connect_id && j1_right_connect_id != -1 && j1_bot_connect_id != -1 ) {
		jungles[ j1_bot_connect_id ] = jungles[ j1_right_connect_id ];
	}
	
	if(j1_left_connect_id != j1_right_connect_id && j1_left_connect_id != -1 && j1_right_connect_id != -1 ) {
		jungles[ j1_left_connect_id ] = jungles[ j1_right_connect_id ];
	}
	
	
	// merge j2
	if(j2_top_connect_id != j2_right_connect_id && j2_top_connect_id != -1 && j2_right_connect_id != -1 ) {
		jungles[ j2_right_connect_id ] = jungles[ j2_top_connect_id ];
	}
	if(j2_top_connect_id != j2_left_connect_id && j2_top_connect_id != -1 && j2_left_connect_id != -1 ) {
		jungles[ j2_left_connect_id ] = jungles[ j2_top_connect_id ];
	}
	if(j2_top_connect_id != j2_bot_connect_id && j2_top_connect_id != -1 && j2_bot_connect_id != -1 ) {
		jungles[ j2_bot_connect_id ] = jungles[ j2_top_connect_id ];
	}
	
	if(j2_left_connect_id != j2_bot_connect_id && j2_left_connect_id != -1 && j2_bot_connect_id != -1 ) {
		jungles[ j2_bot_connect_id ] = jungles[ j2_left_connect_id ];
	}
	if(j2_right_connect_id != j2_bot_connect_id && j2_right_connect_id != -1 && j2_bot_connect_id != -1 ) {
		jungles[ j2_bot_connect_id ] = jungles[ j2_right_connect_id ];
	}
	
	if(j2_left_connect_id != j2_right_connect_id && j2_left_connect_id != -1 && j2_right_connect_id != -1 ) {
		jungles[ j2_left_connect_id ] = jungles[ j2_right_connect_id ];
	}
	
	
	// merge j3
	if(j3_top_connect_id != j3_right_connect_id && j3_top_connect_id != -1 && j3_right_connect_id != -1 ) {
		jungles[ j3_right_connect_id ] = jungles[ j3_top_connect_id ];
	}
	if(j3_top_connect_id != j3_left_connect_id && j3_top_connect_id != -1 && j3_left_connect_id != -1 ) {
		jungles[ j3_left_connect_id ] = jungles[ j3_top_connect_id ];
	}
	if(j3_top_connect_id != j3_bot_connect_id && j3_top_connect_id != -1 && j3_bot_connect_id != -1 ) {
		jungles[ j3_bot_connect_id ] = jungles[ j3_top_connect_id ];
	}
	
	if(j3_left_connect_id != j3_bot_connect_id && j3_left_connect_id != -1 && j3_bot_connect_id != -1 ) {
		jungles[ j3_bot_connect_id ] = jungles[ j3_left_connect_id ];
	}
	if(j3_right_connect_id != j3_bot_connect_id && j3_right_connect_id != -1 && j3_bot_connect_id != -1 ) {
		jungles[ j3_bot_connect_id ] = jungles[ j3_right_connect_id ];
	}
	
	if(j3_left_connect_id != j3_right_connect_id && j3_left_connect_id != -1 && j3_right_connect_id != -1 ) {
		jungles[ j3_left_connect_id ] = jungles[ j3_right_connect_id ];
	}
	
	
	// merge j4
	if(j4_top_connect_id != j4_right_connect_id && j4_top_connect_id != -1 && j4_right_connect_id != -1 ) {
		jungles[ j4_right_connect_id ] = jungles[ j4_top_connect_id ];
	}
	if(j4_top_connect_id != j4_left_connect_id && j4_top_connect_id != -1 && j4_left_connect_id != -1 ) {
		jungles[ j4_left_connect_id ] = jungles[ j4_top_connect_id ];
	}
	if(j4_top_connect_id != j4_bot_connect_id && j4_top_connect_id != -1 && j4_bot_connect_id != -1 ) {
		jungles[ j4_bot_connect_id ] = jungles[ j4_top_connect_id ];
	}
	
	if(j4_left_connect_id != j4_bot_connect_id && j4_left_connect_id != -1 && j4_bot_connect_id != -1 ) {
		jungles[ j4_bot_connect_id ] = jungles[ j4_left_connect_id ];
	}
	if(j4_right_connect_id != j4_bot_connect_id && j4_right_connect_id != -1 && j4_bot_connect_id != -1 ) {
		jungles[ j4_bot_connect_id ] = jungles[ j4_right_connect_id ];
	}
	if(j4_left_connect_id != j4_right_connect_id && j4_left_connect_id != -1 && j4_right_connect_id != -1 ) {
		jungles[ j4_left_connect_id ] = jungles[ j4_right_connect_id ];
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
	
	board[i][j] = *card;            // replace with new card
	
	printFeatures();

	// which cell each region is located in
	int L1 = 10, L2 = 10, J1 = 10, J2 = 10, J3 = 10, J4 = 10, T1 = 10, T2 = 10, T3 = 10, T4 = 10;
	if(zone > 0) {
		cout << "PLACE TIGER ON THIS CARD AT ZONE " << zone << endl;
		card->printCells(L1, L2, J1, J2, J3, J4, T1, T2, T3, T4);
		if (zone == L1) {
			if(card->l1 != NULL) {
				lakes[  card->l1->getId() ].owner = playerID;
			}
		}
		else if (zone == L2) {
			if(card->l2 != NULL) {
			   lakes[  card->l2->getId() ].owner = playerID;
			}
		}
		else if (zone == J1) {
			if(card->j1 != NULL) {
				jungles[  card->j1->getId() ].owner = playerID;
			}
		}
		else if (zone == J2) {
			if(card->j2 != NULL) {
				jungles[  card->j2->getId() ].owner = playerID;
			}
		}
		else if (zone == J3) {
			if(card->j3 != NULL) {
			 jungles[  card->j3->getId() ].owner = playerID;   
			}
		}
		else if (zone == J4) {
			if(card->j4 != NULL) {
			 jungles[  card->j4->getId() ].owner = playerID;
			}
		}
		else if (zone == T1) {
			if(card->t1 != NULL) {
			  trails[  card->t1->getId() ].owner = playerID;
			}
		}
		else if (zone == T2) {
			if(card->t2 != NULL) {
			 trails[  card->t2->getId() ].owner = playerID;
			}
		}
		else if (zone == T3) {
			if(card->t3 != NULL) {
				trails[  card->t3->getId() ].owner = playerID;
			}
		}
		else if (zone == T4) {
			if(card->t4 != NULL) {
			 trails[  card->t4->getId() ].owner = playerID;
			}
		}
	}
	
	//placeTiger()?
	//printBoard();
	markavail(i, j, card);
	return true;
}


void Board::markavail(int i, int j, Card* card) {
	cout << "i is: " << i << endl;
	cout << "j is: " << j << endl;
	// Deleting current location

	for (list<Coords*>::iterator iter = markedtiles.begin(); iter != markedtiles.end();) {
		if((*iter)->icoord == i && (*iter)->jcoord == j) {
			iter = markedtiles.erase(iter);
		}
		else {
			++iter;
		}
	}

	if(board[i-1][j].getId() == -1) {
		Coords* temp2 = new Coords(i-1, j);
		cout << "markavail i-1: " << temp2->icoord << ", " << temp2->jcoord << endl;
		markedtiles.push_back(temp2);
	}

	if(board[i+1][j].getId() == -1) {
		Coords* temp3 = new Coords(i+1, j);
		cout << "markavail i+1: " << temp3->icoord << ", " << temp3->jcoord << endl;
		markedtiles.push_back(temp3);
	}

	if(board[i][j-1].getId() == -1) {
		Coords* temp4 = new Coords(i, j-1);
		cout << "markavail j-1: " << temp4->icoord << ", " << temp4->jcoord << endl;
		markedtiles.push_back(temp4);
	}

	if(board[i][j+1].getId() == -1) {
		Coords* temp5 = new Coords(i, j+1);
		cout << "markavail i+1: " << temp5->icoord << ", " << temp5->jcoord << endl;
		markedtiles.push_back(temp5);
	}
	
	cout << endl << "Marked tile contents" << endl;
	int k = 0;
	for (list<Coords*>::const_iterator iter = markedtiles.begin(); iter != markedtiles.end(); ++iter) {
		cout << "Space " << k << ": " << (*iter)->icoord << "," <<(*iter)->jcoord << endl;
		k++;
	}

	/*
	cout << "before unique markedtiles is " << markedtiles.size() << " big." << endl;
	markedtiles.unique();
	cout << "after unique markedtiles is " << markedtiles.size() << " big." << endl;
	*/
}

void Board::updatePossibleMoves(Card * card) { // possible moves based on board state and current card
	
	bool works = false;
	for (list<Coords*>::const_iterator iter = markedtiles.begin(); iter != markedtiles.end(); ++iter) {
		Moves* temp = new Moves((*iter)->icoord, (*iter)->jcoord);

		for(int i = 0; i < 4; i++) {
			cout << "iter coords: " << (*iter)->icoord << ", " << (*iter)->jcoord << endl;
			if(checkIfFits((*iter)->icoord, (*iter)->jcoord, card) == true) {
				temp->possibleorientations[i] = 1;
				works = true;
			}
			//cout << endl << "before the rotate" << endl;
			card->rotate();
			//cout << endl << "passed the rotate"<< endl;
		}

		if(works == true) {
			possibleMoves.push_back(temp);
			works = false;
		}
	}
	
	//Printing possible moves
	cout << endl;
	int i = 0;
	printBoard();
	card->printCard(); 
	for (list<Moves*>::const_iterator iter = possibleMoves.begin(); iter != possibleMoves.end(); ++iter) {
		cout << "Possible move #" << i << ": " << endl << "icoord: " << (*iter)->icoord 
		<< endl << "jcoord: " << (*iter)->jcoord << endl 
		<< "orientations: [" << (*iter)->possibleorientations[0] << ']'
		<< "[" << (*iter)->possibleorientations[1] << ']'
		<< "[" << (*iter)->possibleorientations[2] << ']'
		<< "[" << (*iter)->possibleorientations[3] << ']' << endl << endl;
		i++;
	}
}

void Board::refreshPossibleMoves() {
	cout << endl << "did we clear?" << endl;
	possibleMoves.clear();
	cout << endl << "we cleared" << endl;
}

bool Board::checkIfFits(int i, int j, Card * card ) {   // i is row, j is col
	
	bool result = false;
	
	// check that the sides match OR are next to open space
	
	if((i == 0          || board[i-1][j].botEdge->type == card->topEdge->type    || board[i-1][j].botEdge->type == 'o') &&           // check top
		(i == ROWS-1    || board[i+1][j].topEdge->type == card->botEdge->type    || board[i+1][j].topEdge->type =='o') &&      // check bot
		(j == 0         || board[i][j-1].rightEdge->type == card->leftEdge->type || board[i][j-1].rightEdge->type == 'o') &&     // check to left
		(j == COLS-1    || board[i][j+1].leftEdge->type == card->rightEdge->type || board[i][j+1].leftEdge->type == 'o')) {    // check to right    
		result = true;
	}
	
	return result;
}


/*  TL  TOP  TR
 ML  MID  MR
 BL  BOT  BR   */
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
}

Card Board::getCard(int i, int j) {
	return board[i][j];
}

void Board::printCardRegions(int i, int j) {
	if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  
		return;
	}
	cout << "\n----------------------------------------------------" << endl;
	cout << "card [" << (j-5) << "][" << -(i-5) << "] :" << endl;
	if(board[i][j].l1 != NULL) {
		cout << "lake   1 belongs to lake   # " << (board[i][j]).l1->getId() << endl;
	}
	if(board[i][j].l2 != NULL) {
		cout << "lake   2 belongs to lake   # " << board[i][j].l2->getId() << endl;
	}
	if(board[i][j].t1 != NULL) {
		cout << "trail  1 belongs to trail  # " << board[i][j].t1->getId() << endl;
	}
	if(board[i][j].t2 != NULL) {
		cout << "trail  2 belongs to trail  # " << board[i][j].t2->getId() << endl;
	}
	if(board[i][j].t3 != NULL) {
		cout << "trail  3 belongs to trail  # " << board[i][j].t3->getId() << endl;
	}
	if(board[i][j].t4 != NULL) {
		cout << "trail  4 belongs to trail  # " << board[i][j].t4->getId() << endl;
	}
	if(board[i][j].j1 != NULL) {
		cout << "jungle 1 belongs to jungle # " << board[i][j].j1->getId() << endl;
	}
	if(board[i][j].j2 != NULL) {
		cout << "jungle 2 belongs to jungle # " << board[i][j].j2->getId() << endl;
	}
	if(board[i][j].j3 != NULL) {
		cout << "jungle 3 belongs to jungle # " << board[i][j].j3->getId() << endl;
	}
	if(board[i][j].j4 != NULL) {
		cout << "jungle 4 belongs to jungle # " << board[i][j].j4->getId() << endl;
	}
	cout << endl;
}

void Board::printFeatures() {
   
	cout << "LAKES:" << endl;
	for(int i = 0; i < 10; i++) {
		
		cout << "lakes " << i << ":" << endl;
		cout << "       numEdges = " << lakes[i].edgeConnects << endl;
		cout << "          owner = " << lakes[i].owner << endl;
	}
}



