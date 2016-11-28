#include <iostream>
#include <string>
#include "inout.h"
using namespace std;

Input::Input()
{
  //empty constructor
}

void Input::takeInput(string message){
    string::size_type sz;   // alias of size_t
    size_t start, end;

    if(message.find("PLEASE WAIT FOR THE NEXT CHALLENGE") != -1)
    {
      tournyOpen = true;
    }

    if(message.find("THANK YOU FOR PLAYING!") != -1)
    {
      tournyOpen = false;
    }

    if(message.find("NEW CHALLENGE") != -1)
    {
      challengeOpen = true;
    }

    if(message.find("END OF CHALLENGES") != -1 || message.find("NEXT CHALLENGE TO BEGIN") != -1)
    {
      challengeOpen = false;
    }  

    if(message.find("MATCH BEGINS") != -1)
    {
      gameOpen = true;
    }

    if(message.find("OVER PLAYER") != -1)
    {
      gameOpen = false;
    }      
/*
    if(message[1] == 'T'){
         origin = true;
         start = message.find("IS");
         startTile = message.substr(start+3, 5);
         originCoord = make_pair(message[start+12]-'0', message[start+14]-'0');
         origOrientation = message[start+16]-'0';
         message = "";
    }
*/
    //THE REMAINING 6 TILES ARE [ TLTTP LJTJ- JLJL- JJTJX JLTTB TLLT- ]
    if(message[6]=='M'){
      //Store Tiles & Think for 15s boolean?
      int n = stoi(message.substr(14, 2));
      
      start = message.find("[");
      end = message.find("]");
      tiles = message.substr(start+2, (end-1)-(start+2));
      //Think for 15s...
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
      tile = message.substr(start+6, 5); //Place xxxxx
      makeMove = true;
      message = "";
    }

}
