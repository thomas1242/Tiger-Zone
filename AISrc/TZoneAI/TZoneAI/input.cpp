#include <iostream>
#include <string>
#include "inout.h"
using namespace std;


void Input::takeInput(){

    getline(cin, message);

    if(message[2] == 'I'){//THIS IS SPARTA
        tournyStart = true;
        message = "";
    }

    if(message[5] == '!') {//HELLO!
        signin = true;
        message = "";
    }
    if(message[6]=='M'){ //THE REMAINING # TILES ARE [ ... ]
      int start = message.find("[");
      int end = message.find("]");
      tiles = message.substr(start+1, end-1);
    }
    //MAKE YOUR MOVE IN GAME A WITHIN 1 SECOND: MOVE 1 PLACE TLTTP
    if (message[2] == 'K') {
        game = message[23]; //Game letter
        timeMove = (int)message[32]; //Within # Second
        moveCount = (int)message[47]; //Move #
        tile = message.substr(54,59); //Place xxxxx
        makeMove = true;
        message = "";
    }

    if (message[7] == 'C') { //END OF CHALLENGES
        noInput = true;
        message = "";
    }

}
