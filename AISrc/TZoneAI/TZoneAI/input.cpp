#include <iostream>
#include <string>
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
    //if(message[1] == 'T'){}

    //THE REMAINING 6 TILES ARE [ TLTTP LJTJ- JLJL- JJTJX JLTTB TLLT- ]
    if(message[6]=='M'){
      //Store Tiles & Think for 15s boolean?
      int n = message[14];
      start = message.find("[");
      tiles = message.substr(start+1, 6*n);
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
      moveCount = stoi(temp2,&sz); //Move #

      start = message.find("PLACE");
      tile = message.substr(start+6); //Place xxxxx
      makeMove = true;
      message = "";
    }

    if (message[7] == 'C') { //END OF CHALLENGES
        noInput = true;
        message = "";
    }

}
