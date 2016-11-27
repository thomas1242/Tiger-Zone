#include <iostream>
#include <string>
#include <utility>
#include "inout.h"
using namespace std;


void Input::takeInput(){
    string::size_type sz;   // alias of size_t
    size_t start, end;
    getline(cin, message);

    if(message[2] == 'I'){//THIS IS SPARTA
      tournyStart = true;
      message = "";
    }
    if(message[5] == '!') {//HELLO!
      signin = true;
      message = "";
    }
    //STARTING TILE IS TLTJ- AT 0 0 0
    //I dont think this if statement is necessary. Since originCoord,
    /*origOrientation, and startTile are fixed. From what it looks like.
    if(message[1] == 'T'){
      origin = true;
      start = message.find("IS");
      startTile = message.substr(start+3, 5);
      originCoord = make_pair(message[start+12]-'0', message[start+14]-'0');
      origOrientation = message[start+16]-'0';
      message = "";
    }*/
    //THE REMAINING 6 TILES ARE [ TLTTP LJTJ- JLJL- JJTJX JLTTB TLLT- ]
    if(message[6]=='M'){
      //Store Tiles & Think for 15s boolean?
      theTiles = true;
      int n = message[14];
      start = message.find("[");
      end = message.find("]");
      tiles = message.substr(start+2, (end-1)-(start+2));
      message = "";
    }
    //MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND: MOVE 1 PLACE TLTTP
    //MAKE YOUR MOVE IN GAME A WITHIN 23 SECOND: MOVE 23 PLACE TLTTP
    if (message[2] == 'K') {
      string temp1,temp2;
      game = message[23]; //Game letter

      start = message.find("WITHIN");
      end = message.find("SECOND");
      temp1 = message.substr(start+6, (end-1)-(start+6));
      timeMove = stoi(temp1,&sz); //Within # Second

      start = message.find(": MOVE ");
      end = message.find("PLACE");
      temp2 = message.substr(start+6, (end-1)-(start+6));
      moveCount = stoi(temp2,&sz); //Move # place

      start = message.find("PLACE");
      tile = message.substr(start+6); //Place xxxxx
      makeMove = true;
      message = "";
    }

    if (message[4] == 'K') { //THANK YOU FOR PLAYING! GOODBYE
      noInput = true;
      message = "";
    }

}
