#include "board.h"
#include "card.h"
#include "deck.h"
#include "moves.h"
#include "coords.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

Board::Board(Card * card) {                            // board constructor
        
    board = new Card * [ROWS];              // board is initially all open space ( cards with id = -1 )
    for(int i = 0; i < ROWS; ++i) {
        board[i] = new Card[COLS];
    }
    
    numJungles = 0;
    numTrails = 0;
    numLakes = 0;
    
    jungles = new Jungle[10];
    trails = new Trail[10];
    lakes = new Lake[10];
    for(int i = 0; i < 10; i++) {
        trails[i].setId(i );
        lakes[i].setId(i);
    }
    
    
    cout << "Put center card on new board" << endl;
    placeCard(ROWS/2, COLS/2, card, 0);        // place center card on the board
}


bool Board::placeCard(int i, int j, Card * card, int rotations) {
    
    if(i < 0 || j < 0 || i >= ROWS || j >= COLS) {  // for GUI, if user clicks out of bounds
        return false;
    }
/*    
    // before placing this card on the board, make sure the location is valid
    if( !possibleMoves[i][j] ) {
        cout << "Cannot place card " << card->getId() << " at (" << i << ',' << j << ']' << endl;
        return false;
    }
*/
    
    while( rotations !=0) {
        card->rotate();                     // rotate card until it fits at the valid location
        rotations--;
    }
    
    cout << "Placed card " << card->getId() << " at [" << i << ',' << j << ']' << endl;
    board[i][j] = *card;            // replace with new card
    printBoard();

    
    bool lakeOne = false;
    bool lakeTwo = false;
    if(card->l1 != NULL) {
        lakeOne = true;
        cout << "card has l1" << endl;
    }
    if(card->l2 != NULL) {
        lakeTwo = true;
        cout << "card has l2" << endl;
    }
    
    
    if( card->getTop() == 'L')  {                                       // this card has lake face on top edge
       
        if(i > 0 && board[i-1][j].botEdge->type == 'L') {          // card above has lake face on bot edge
            if(card->topEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "top has l1 connecting to side with id " << board[i-1][j].botEdge->l1->getId() << endl;
                card->l1 = &lakes[ board[i-1][j].botEdge->l1->getId() ];
                lakeOne = false;
            }
            if(card->topEdge->l1 == card->l2) {
                cout << "top has l2 connecting to side with id " << board[i-1][j].botEdge->l1->getId() << endl;
                card->l2 = &lakes[ board[i-1][j].botEdge->l1->getId() ];
                lakeTwo = false;
            }
            card->reConnect();
            cout << "this cards top edge now has id: " << card->topEdge->l1->getId() << endl;
        }
        
        else {
            if(card->topEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "top has l1 connecting to nothing" << endl;
            //    lakeOne = true;
            }
            if(card->topEdge->l1 == card->l2) {
                cout << "top has l2 connecting to nothing" << endl;
            //    lakeTwo = true;
            }
        }
        
    }
    
    if( card->getBot() == 'L')  {                                       // this card has lake face on top edge
        
        if(i < ROWS - 1 && board[i+1][j].topEdge->type == 'L') {          // card above has lake face on bot edge
            if(card->botEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "bot has l1 connecting" << endl;
                card->l1 = &lakes[ board[i+1][j].topEdge->l1->getId() ];
                lakeOne = false;
            }
            if(card->botEdge->l1 == card->l2) {
                cout << "bot has l2 connecting" << endl;
                card->l2 = &lakes[ board[i+1][j].topEdge->l1->getId() ];
                lakeTwo = false;
            }
            card->reConnect();
            cout << "this cards bot edge now has id: " << card->botEdge->l1->getId() << endl;
        }
        
        else {
            if(card->botEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "bot has l1 connecting to nothing" << endl;
             //   lakeOne = true;
            }
            if(card->botEdge->l1 == card->l2) {
                cout << "bot has l2 connecting to nothing" << endl;
            //    lakeTwo = true;
            }
        }
        
    }

    if( card->getLeft() == 'L')  {                                       // this card has lake face on top edge
        
        if(j > 0 && board[i][j-1].rightEdge->type == 'L') {          // card above has lake face on bot edge
            if(card->leftEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "left has l1 connecting to side with id " << board[i][j-1].rightEdge->l1->getId() << endl;
                card->l1 = &lakes[ board[i][j-1].rightEdge->l1->getId() ];
                lakeOne = false;
            }
            if(card->leftEdge->l1 == card->l2) {
                cout << "left has l2 connecting to side with id " << board[i][j-1].rightEdge->l1->getId() << endl;
                card->l2 = &lakes[ board[i][j-1].rightEdge->l1->getId() ];
                lakeTwo = false;
            }
            card->reConnect();
            cout << "this cards left edge now has id: " << card->leftEdge->l1->getId() << endl;
        }
        
        else {
            if(card->leftEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "left has l1 connecting to nothing" << endl;
          //      lakeOne = true;
            }
            if(card->leftEdge->l1 == card->l2) {
                cout << "left has l2 connecting to nothing" << endl;
          //      lakeTwo = true;
            }
        }
        
    }
    
    if( card->getRight() == 'L')  {                                       // this card has lake face on top edge
        
        if(j < COLS - 1 && board[i][j+1].leftEdge->type == 'L') {          // card above has lake face on bot edge
            if(card->rightEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "right has l1 connecting" << endl;
                card->l1 = &lakes[ board[i][j+1].leftEdge->l1->getId() ];
                lakeOne = false;
            }
            if(card->rightEdge->l1 == card->l2) {
                cout << "right has l2 connecting" << endl;
                card->l2 = &lakes[ board[i][j+1].leftEdge->l1->getId() ];
                lakeTwo = false;
            }
            card->reConnect();
            cout << "this cards right edge now has id: " << card->rightEdge->l1->getId() << endl;
        }
        
        else {
            if(card->rightEdge->l1 == card->l1) {     // which lake region does this cards top edge connect to
                cout << "right has l1 connecting to nothing" << endl;
        //        lakeOne = true;
            }
            if(card->rightEdge->l1 == card->l2) {
                cout << "right has l2 connecting to nothing" << endl;
        //        lakeTwo = true;
            }
        }
        
    }

    
    if(lakeOne) {
        numLakes++;
        cout << "new l1 at lakes[" << numLakes << "]" << endl;
        card->l1 = &lakes[ numLakes ];
        cout << "card->l1.getId() = " << card->l1->getId() << endl;
        card->reConnect();
    }
    if(lakeTwo) {
        numLakes++;
        cout << "new l2 at lakes[" << numLakes << "]" << endl;
        card->l2 = &lakes[ numLakes ];
         cout << "card->l2.getId() = " << card->l2->getId() << endl;
        card->reConnect();
    }
    
    
//    if(card->topEdge->t1 != NULL) {
//        cout <<  "topEdge->t1 id = " << card->topEdge->t1->getId() << endl;
//        cout <<  "trails[0] id = " << trails[0].getId() << endl;
//        card->t1 = &trails[0];
//        card->topEdge->t1 = card->t1;
//    }
    
    //cout <<  "topEdge->t1 id = " << card->topEdge->t1->getId() << endl;

    
//============================================================================================================
    int numConnects = 0;
    bool hasTrail;
    if( card->getTop() == 'T' || card->getBot() == 'T' || card->getRight() == 'T' || card->getLeft() == 'T') {
        hasTrail = true;
    }
    
    
    
    
    
    
    
    
//    bool newt1 = true;
//    bool newt2 = true;
//    bool newt3 = true;
//    bool newt4 = true;
//    
//    
//    //
//    if( card->getTop() == 'T' ) // card has trail top face
//    {
//        if(i > 0 && board[i-1][j].botEdge->type == 'T') {
//            
//            
//            
//        }
//        
//    }
//    //
//    
//    
//    if( card->getTop() == 'T') // card has trail top face
//    {
//        if(i > 0 && board[i-1][j].botEdge->type == 'T') { // card connects to a trail above
//           
//            if(card->topEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                newt1 = false;
//            }
//            if (card->topEdge->t1 == card->t2) {
//                card->t2 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                newt2 = false;
//            }
//            if (card->topEdge->t1 == card->t3) {
//                card->t3 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                newt3 = false;
//            }
//            if (card->topEdge->t1 == card->t4) {
//                card->t4 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                newt4 = false;
//            }
//            card->reConnect();
//            cout << "trail id of top connecting card = " << board[i-1][j].botEdge->t1->getId() << endl;
//        }
//        else if (i > 0 && board[i-1][j].botEdge->type != 'T') {
//            if(card->topEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;
//            }
//            else if (card->topEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->topEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->topEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//          //  card->reConnect();
//        }
//        card->reConnect();
//    }
//    if( card->getBot() == 'T') // card has trail bot face
//    {
//        if(i < ROWS - 1 && board[i+1][j].topEdge->t1 != NULL) { // card connects to a trail below
//            if(card->botEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->botEdge->t1 == card->t2) {
//                newt2 = false;
//                card->t2 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            else if (card->botEdge->t1 == card->t3) {
//                newt3 = false;
//                card->t3 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            else if (card->botEdge->t1 == card->t4) {
//                newt4 = false;
//                card->t4 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            card->reConnect();
//            cout << "trail id of bot connecting card = " << board[i+1][j].topEdge->t1->getId() << endl;
//        }
//        else if (i < ROWS - 1 && board[i+1][j].topEdge->t1 == NULL) {
//            if(card->botEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//         //   card->reConnect();
//        }
//        card->reConnect();
//    }
//    if( card->getRight() == 'T') // card has trail right face
//    {
//        if(j < COLS - 1 && board[i][j+1].leftEdge->t1 != NULL) {  // card connects to a trail right side
//            if(card->rightEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->rightEdge->t1 == card->t2) {
//                card->t2 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt2 = false;
//            }
//            else if (card->rightEdge->t1 == card->t3) {
//                card->t3 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt3 = false;
//            }
//            else if (card->rightEdge->t1 == card->t4) {
//                card->t4 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt4 = false;
//            }
//            card->reConnect();
//            cout << "trail id of right connecting card = " << board[i][j+1].leftEdge->t1->getId() << endl;
//        }
//        else if (j < COLS - 1 && board[i][j+1].leftEdge->t1 == NULL) {
//            if(card->rightEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//         //   card->reConnect();
//        }
//        card->reConnect();
//    }
//    if( card->getLeft() == 'T') // card has trail right face
//    {
//        if(j > 0 && board[i][j-1].rightEdge->t1 != NULL) {  // card connects to a trail right side
//            if(card->leftEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->leftEdge->t1 == card->t2) {
//                card->t2 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt2 = false;
//            }
//            else if (card->leftEdge->t1 == card->t3) {
//                card->t3 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt3 = false;
//            }
//            else if (card->leftEdge->t1 == card->t4) {
//                card->t4 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt4 = false;
//            }
//            card->reConnect();
//            cout << "trail id of left connecting card = " << board[i][j-1].rightEdge->t1->getId() << endl;
//        }
//        else if (j > 0 && board[i][j-1].rightEdge->t1 == NULL) {
//            if(card->leftEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;            }
//            else if (card->leftEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->leftEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->leftEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//          //  card->reConnect();
//        }
//        card->reConnect();
//    }
//    
//    
//    if( newt1 && card->t1 != NULL){
//        numTrails++;
//        cout << "new t1 at trails[" << numTrails << "]" << endl;
//        card->t1 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt2  && card->t2 != NULL) {
//        numTrails++;
//        cout << "new t2 at trails[" << numTrails << "]" << endl;
//        card->t2 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt3  && card->t3 != NULL) {
//        numTrails++;
//        cout << "new t3 at trails[" << numTrails << "]" << endl;
//        card->t3 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt4  && card->t4 != NULL) {
//        numTrails++;
//        cout << "new t4 at trails[" << numTrails << "]" << endl;
//        card->t4 = &trails[ numTrails ];
//        card->reConnect();
//    }
    
//    bool newt1 = true;
//    bool newt2 = true;
//    bool newt3 = true;
//    bool newt4 = true;
//    
//    
//    //
//    if( card->getTop() == 'T' ) // card has trail top face
//    {
//        if(i > 0 && board[i-1][j].botEdge->type == 'T') {
//            
//        }
//    
//    }
//    //
//    
//    
//     if( card->getTop() == 'T') // card has trail top face
//     {
//         if(i > 0 && board[i-1][j].botEdge->type == 'T') { // card connects to a trail above
//             if(card->topEdge->t1 == card->t1) {                                // which trail region does it connect to
//                 card->t1 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                 newt1 = false;
//             }
//             if (card->topEdge->t1 == card->t2) {
//                 card->t2 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                 newt2 = false;
//             }
//             if (card->topEdge->t1 == card->t3) {
//                 card->t3 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                 newt3 = false;
//             }
//             if (card->topEdge->t1 == card->t4) {
//                 card->t4 = &trails[ board[i-1][j].botEdge->t1->getId() ];
//                 newt4 = false;
//             }
//             card->reConnect();
//             cout << "trail id of top connecting card = " << board[i-1][j].botEdge->t1->getId() << endl;
//         }
//         else if (i > 0 && board[i-1][j].botEdge->type != 'T') {
//             if(card->topEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                 newt1 = (newt1 == false)?false:true;
//             }
//             else if (card->topEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                 newt2 = (newt2 == false)?false:true;
//             }
//             else if (card->topEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                 newt3 = (newt3 == false)?false:true;
//             }
//             else if (card->topEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                 newt4 = (newt4 == false)?false:true;
//             }
//             card->reConnect();
//         }
//         card->reConnect();
//    }
//    if( card->getBot() == 'T') // card has trail bot face
//    {
//        if(i < ROWS - 1 && board[i+1][j].topEdge->t1 != NULL) { // card connects to a trail below
//            if(card->botEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->botEdge->t1 == card->t2) {
//                newt2 = false;
//                card->t2 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            else if (card->botEdge->t1 == card->t3) {
//                newt3 = false;
//                card->t3 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            else if (card->botEdge->t1 == card->t4) {
//                newt4 = false;
//                card->t4 = &trails[ board[i+1][j].topEdge->t1->getId() ];
//            }
//            card->reConnect();
//            cout << "trail id of bot connecting card = " << board[i+1][j].topEdge->t1->getId() << endl;
//        }
//        else if (i < ROWS - 1 && board[i+1][j].topEdge->t1 == NULL) {
//            if(card->botEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->botEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//            card->reConnect();
//        }
//        card->reConnect();
//    }
//    if( card->getRight() == 'T') // card has trail right face
//    {
//        if(j < COLS - 1 && board[i][j+1].leftEdge->t1 != NULL) {  // card connects to a trail right side
//            if(card->rightEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->rightEdge->t1 == card->t2) {
//                card->t2 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt2 = false;
//            }
//            else if (card->rightEdge->t1 == card->t3) {
//                card->t3 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt3 = false;
//            }
//            else if (card->rightEdge->t1 == card->t4) {
//                card->t4 = &trails[ board[i][j+1].leftEdge->t1->getId() ];
//                newt4 = false;
//            }
//            card->reConnect();
//            cout << "trail id of right connecting card = " << board[i][j+1].leftEdge->t1->getId() << endl;
//        }
//        else if (j < COLS - 1 && board[i][j+1].leftEdge->t1 == NULL) {
//            if(card->rightEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->rightEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//            card->reConnect();
//        }
//        card->reConnect();
//    }
//    if( card->getLeft() == 'T') // card has trail right face
//    {
//        if(j > 0 && board[i][j-1].rightEdge->t1 != NULL) {  // card connects to a trail right side
//            if(card->leftEdge->t1 == card->t1) {                                // which trail region does it connect to
//                card->t1 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt1 = false;
//            }
//            else if (card->leftEdge->t1 == card->t2) {
//                card->t2 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt2 = false;
//            }
//            else if (card->leftEdge->t1 == card->t3) {
//                card->t3 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt3 = false;
//            }
//            else if (card->leftEdge->t1 == card->t4) {
//                card->t4 = &trails[ board[i][j-1].rightEdge->t1->getId() ];
//                newt4 = false;
//            }
//            card->reConnect();
//            cout << "trail id of left connecting card = " << board[i][j-1].rightEdge->t1->getId() << endl;
//        }
//        else if (j > 0 && board[i][j-1].rightEdge->t1 == NULL) {
//            if(card->leftEdge->t1 == card->t1 && card->t1->getId() == 0) {                                // connects to nothing, make new trail
//                newt1 = (newt1 == false)?false:true;            }
//            else if (card->leftEdge->t1 == card->t2 && card->t2->getId() == 0) {
//                newt2 = (newt2 == false)?false:true;
//            }
//            else if (card->leftEdge->t1 == card->t3 && card->t3->getId() == 0) {
//                newt3 = (newt3 == false)?false:true;
//            }
//            else if (card->leftEdge->t1 == card->t4 && card->t4->getId() == 0) {
//                newt4 = (newt4 == false)?false:true;
//            }
//            card->reConnect();
//        }
//        card->reConnect();
//    }
//    
//    
//    if( newt1 && card->t1 != NULL){
//        numTrails++;
//        cout << "new t1 at trails[" << numTrails << "]" << endl;
//        card->t1 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt2  && card->t2 != NULL) {
//        numTrails++;
//        cout << "new t2 at trails[" << numTrails << "]" << endl;
//        card->t2 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt3  && card->t3 != NULL) {
//        numTrails++;
//        cout << "new t3 at trails[" << numTrails << "]" << endl;
//        card->t3 = &trails[ numTrails ];
//        card->reConnect();
//    }
//    if ( newt4  && card->t4 != NULL) {
//        numTrails++;
//        cout << "new t4 at trails[" << numTrails << "]" << endl;
//        card->t4 = &trails[ numTrails ];
//        card->reConnect();
//    }
//
//    if( card->getBot() == 'T' && i < ROWS - 1 && board[i+1][j].topEdge->t1 != NULL) // new card connects to bottom trail
//    {
//        cout << "trail id of bot connecting card = " << board[i+1][j].topEdge->t1->getId() << endl;
//        numConnects++;
//    }
//    if( card->getRight() == 'T' && j < COLS - 1 && board[i][j+1].leftEdge->t1 != NULL) // new card connects to right trail
//    {
//        cout << "trail id of right connecting card = " << board[i][j+1].leftEdge->t1->getId() << endl;
//        numConnects++;
//    }
//    if( card->getLeft() == 'T' && j > 0 && board[i][j-1].rightEdge->t1 != NULL) // new card connects to left trail
//    {
//        cout << "trail id of left connecting card = " << board[i][j-1].rightEdge->t1->getId() << endl;
//        numConnects++;
//    }
     //  cout << " NUMBER CONNECTIONS = " << numConnects << endl;
    
        
    if(card->t1 != NULL) {      // card has t1 region
            
    }
    if(card->t2 != NULL) {      // card has t2 region
            
    }
    if(card->t3 != NULL) {      // card has t3 region
            
    }
    if(card->t4 != NULL) {      // card has t4 region
            
    }
        
    

//============================================================================================================
    
//    // check edges of all features and update them
//    int numConnections = 0;
//    bool hasConnection = false;
//    
//    // if new tile has a trail(s)
//    if( card->getTop() == 'T' && card->topEdge->t1 == NULL) {
//        if(i > 0 && board[i-1][j].botEdge->t1 != NULL) {    // if connected to trail
//            card->topEdge->t1 = board[i-1][j].botEdge->t1;  // connect
//        }
//        else {
//            card->topEdge->t1 = &trails[ ++numTrails ];
//            trails[ numTrails ].setId(numTrails);
//        }
//    }
//    // if new tile has a trail(s)
//    if( card->getBot() == 'T' && card->botEdge->t1 == NULL) {
//        if(i < ROWS - 1 && board[i+1][j].topEdge->t1 != NULL) {    // if connected to trail
//            card->botEdge->t1 = board[i+1][j].topEdge->t1;  // connect
//        }
//        else {
//            card->botEdge->t1 = &trails[ ++numTrails ];
//            trails[ numTrails ].setId(numTrails);
//        }
//    }
//    
//    
//    
//    if( i > 0 && card->getTop() == 'T' && board[i-1][j].getBot() == 'T') {   //
//       
//        // if trail connect to top
//        numConnections++;
//        
//    }
//    if( j > 0 && card->getLeft() == 'T' && board[i][j-1].getRight() == 'T') {   //
//        
//        // if trail connect to left
//        numConnections++;
//        
//    }
//    if( i < ROWS - 1 && card->getBot() == 'T' && board[i+1][j].getTop() == 'T') {   //
//        numConnections++;
//        // if trail connect to bot
//        
//    }
//    if( j < COLS - 1 && card->getRight() == 'T' && board[i][j+1].getLeft() == 'T') {   //
//        numConnections++;
//        // if trail connect to right
//        
//    }
   
//    cout << " NUMBER CONNECTIONS = " << numConnections << endl;
    
    // rotate option
    // place meeple()
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

    Coords* temp2 = new Coords(i-1, j);
    cout << "markavail i-1: " << temp2->icoord << ", " << temp2->jcoord << endl;
    markedtiles.push_back(temp2);

    Coords* temp3 = new Coords(i+1, j);
    cout << "markavail i+1: " << temp3->icoord << ", " << temp3->jcoord << endl;
    markedtiles.push_back(temp3);

    Coords* temp4 = new Coords(i, j-1);
    cout << "markavail j-1: " << temp4->icoord << ", " << temp4->jcoord << endl;
    markedtiles.push_back(temp4);

    Coords* temp5 = new Coords(i, j+1);
    cout << "markavail i+1: " << temp5->icoord << ", " << temp5->jcoord << endl;
    markedtiles.push_back(temp5);
    
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
        int i = (*iter)->icoord;
        int j = (*iter)->jcoord;
        Moves* temp = new Moves(i, j);

        for(i = 0; i < 4; i++) {
            cout << "iter coords: " << (*iter)->icoord << ", " << (*iter)->jcoord << endl;
            if(checkIfFits((*iter)->icoord, (*iter)->jcoord, card) == true) {
                temp->possibleorientations[i] = 1;
                cout << "FITS" << endl;
                works = true;
            }
            cout << endl << "before the rotate" << endl;
            card->rotate();
            cout << endl << "passed the rotate"<< endl;
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
    for(int i = 0; i < ROWS; i++) {             // for each row
        for(int n = 0; n < 3; n++) {            // 3 'rows' per row
            for(int j = 0; j < COLS; j++) {     // for each col
                if(n == 0) {
                    cout << "   " << board[i][j].getTop() << "   ";
                }
                else if (n == 1) {
                    if(board[i][j].getId() < 10 && board[i][j].getId() > 0) {
                       cout << board[i][j].getLeft() << "  " << board[i][j].getId() << ' ' << board[i][j].getRight() << ' '; 
                    }
                    else {
                         cout << board[i][j].getLeft() << ' ' << board[i][j].getId() << ' ' << board[i][j].getRight() << ' ';
                    }
                }
                else if (n == 2) {
                    cout << "   " << board[i][j].getBot() << "   ";
                }
                cout << ' ';
            }
            /*if( n == 1 ) {
                for(int k = 0; k < COLS; k++) {
                    cout << "  " << board[i][k].getId() << "  ";
                }
            }*/
           cout << endl;
        }
        cout << endl;
    }
}

Card Board::getCard(int i, int j) {
    return board[i][j];
}




