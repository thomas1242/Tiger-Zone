#include <iostream>
#include <string>
#include <utility>
#include "inout.h"
using namespace std;

Input::Input()
{
moveCount = 0;
makeMove = false;
}


void Input::takeInput(string message){
    string::size_type sz;// alias of size_t
    size_t start, end;

    if(message[2] == 'I'){//THIS IS SPARTA
      tournyStart = true;
      message = "";
    }
    if(message[5] == '!') {//HELLO!
      signin = true;
      message = "";
    }
    if(message[0] == 'W'){//WELCOME <pid> PLEASE WAIT...
      start = message.find("WELCOME");
      end = message.find("PLEASE");
      pid = message.substr(start+8, (end-1)-(start+8));
    }
    if(message[2] == 'W'){//NEW CHALLENGE 43 YOU WILL PLAY 56 MATCHES
        start = message.find("CHALLENGE");
        end = message.find("YOU");
        cid = stoi(message.substr(start+9, (end-1)-(start+9)), &sz);
        start = message.find("PLAY");
    end = message.find("MATCHES");
    rounds = stoi(message.substr(start+4, (end-1)-(start+4)), &sz);
    }

    if(message[4] == 'N'){//BEGIN ROUND 32 OF 56
      start = message.find("ROUND");
    end = message.find("OF");
    rid = stoi(message.substr(start+5, (end-1)-(start+5)), &sz);
    }
    if(message[2] == 'U'){//YOUR OPPONENT IS PLAYER <pid>
      start = message.find("PLAYER");

    }
    if(message[1] == 'T'){//STARTING TILE IS TLTJ- AT 0 0 0
      start = message.find("IS");
      startTile = message.substr(start+3, 5);
      start = message.find("AT");
      end = message.find(" ", start+3);
      int x = stoi(message.substr(start+3, end-(start+3)), &sz);//"AT <x> "
      start = message.find(" ", end);
      end = message.find(" ", start+1);
      int y = stoi(message.substr(start, end-(start)), &sz);//"AT <y> "
      originCoord = make_pair(x, y);
      start = message.find(" ", end);
      origOrientation = stoi(message.substr(start), &sz);
      message = "";
    }
    //THE REMAINING 6 TILES ARE [ TLTTP LJTJ- JLJL- JJTJX JLTTB TLLT- ]
    if(message[6]=='M'){
      start = message.find("[");
      end = message.find("]");
      tiles = message.substr(start+2, (end-1)-(start+2));
      message = "";
    }
    if(message[2] == 'T'){//MATCH BEGINS IN <TIME> SECONDS
        start = message.find(" IN ");
        end = message.find("SECONDS");
        timePlan = stoi(message.substr(start+3, (end-1)-(start+3)),&sz);
    }
    if (message[2] == 'K') {//MAKE YOUR MOVE IN GAME A WITHIN 23 SECOND: MOVE 23 PLACE TLTTP
    string temp1,temp2;
    start = message.find("GAME");
    end = message.find("WITHIN");
    gid = message.substr(start+4, (end-1)-(start+4)); //Game letter

	// cout << "GID = " << gid << endl;



    start = message.find("WITHIN");
    end = message.find("SECOND");
    temp1 = message.substr(start+6, (end-1)-(start+6));
    timeMove = stoi(temp1,&sz); //Within # Second

    start = message.find(": MOVE ");
    end = message.find("PLACE");
    temp2 = message.substr(start+6, (end-1)-(start+6));
    //moveCount = stoi(temp2,&sz); //Move # place

    start = message.find("PLACE");
    tile = message.substr(start+6); //Place xxxxx
    cout << "tile: " << tile << "_-_" << endl;
    makeMove = true;
    message = "";
    }
    if(message.find("GAME") != -1 && message.find("PLACED") != -1){//GAME gameID MOVE 99 PLAYER aPlayerName PLACED TTJL AT 43 45 90 NONE
    start = message.find("GAME");//GAME gameID MOVE 99 PLAYER aPlayerName TILE TTJL- UNPLACEABLE ADDED ANOTHER TIGER TO 99 239
    end = message.find("MOVE");
    //gid = message.substr(start+5, (end-1)-(start+5));
    start = end;
    end = message.find("PLAYER");
    cout << "stoi1" << endl;
    //moveCount = stoi(message.substr(start+4, (end-1)-(start+4)), &sz);
    start = end+6;
    end = message.find(" ", start+1);
    pid = message.substr(start+1, end-(start+1));

    if(message.find("PLACED") != string::npos){
      start = message.find("PLACED");
      end = message.find("AT");
      tile = message.substr(start+6, (end-1)-(start+6));
      start = end;
      end = message.find(" ", start+3);
    cout << "stoi2" << endl;
      int x = stoi(message.substr(start+3, end-(start+3)));//"AT <x> "
      start = message.find(" ", end);
      end = message.find(" ", start+1);
     cout << "stoi3" << endl; 
      int y = stoi(message.substr(start, end-(start)));//"AT <y> "
      coord = make_pair(x, y);
      start = message.find(" ", end);
      end = message.find(" ", start+1);
      cout << "stoi4" << endl;
      orientation = stoi(message.substr(start+1, end-(start+1)), &sz);

      if(message.find("NONE") != string::npos){
        //NONE
      }
      else if(message.find("CROCODILE") != string::npos){
        croc = true;
      }
      else{
        tiger = true;
        cout << "stoi5" << endl;
        zone = stoi(message.substr(message.find("TIGER")+5), &sz);

      }
    }
    else{
      start = message.find("TILE");
      end = message.find("UNPLACEABLE");
      tile = message.substr(start+5, (end-1)-(start+5));
      if(message.find("PASSED") != string::npos){
        //PASSED
      }
      else if(message.find("AT") != string::npos){
        start = message.find("AT");
        end = message.find(" ", start+3);
        cout << "stoi6" << endl;
        int x = stoi(message.substr(start+3, end-(start+3)), &sz);//"AT <x> "
        start = message.find(" ", end);
        cout << "stoi7" << endl;
        int y = stoi(message.substr(start), &sz);//"AT <y> "
        coord = make_pair(x, y);
      }
      else{
        start = message.find("TO");
        end = message.find(" ", start+3);
        int x = stoi(message.substr(start+3, end-(start+3)), &sz);//"AT <x> "
        start = message.find(" ", end);
        int y = stoi(message.substr(start), &sz);//"AT <y> "
        coord = make_pair(x, y);
      }
    }
    }
    if (message[4] == 'K') { //THANK YOU FOR PLAYING! GOODBYE
      noInput = true;
      message = "";
    }

    if(message.find("ILLEGAL TILE PLACEMENT") != string::npos)
      {
        forfeit = true;
      }

    if(message.find("ILLEGAL MEEPLE PLACEMENT") != string::npos)
      {
        forfeit = true;
      }

    if(message.find("INVALID MEEPLE PLACEMENT") != string::npos)
      {
        forfeit = true;
      }

  if(message.find("TIMEOUT") != string::npos)
  {
    forfeit = true;
  }

  if(message.find("ILLEGAL MESSAGE RECEIVED") != string::npos)
  {
    forfeit = true;
  }

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
      moveCount = 0;

    }   





}



int Input::convertID(string ID)
{
    if(ID == "JJJJ-"){return 0;}
    if(ID == "JJJJX"){return 1;}
    if(ID == "JJTJX"){return 2;}
    if(ID == "TTTT-"){return 3;}
    if(ID == "TJTJ-"){return 4;}
    if(ID == "TJJT-"){return 5;}
    if(ID == "TJTT-"){return 6;}
    if(ID == "LLLL-"){return 7;}
    if(ID == "JLLL-"){return 8;}
    if(ID == "LLJJ-"){return 9;}
    if(ID == "JLJL-"){return 10;}
    if(ID == "LJLJ-"){return 11;}
    if(ID == "LJJJ-"){return 12;}
    if(ID == "JLLJ-"){return 13;}
    if(ID == "TLJT-"){return 14;}
    if(ID == "TLJTP"){return 15;}
    if(ID == "JLTT-"){return 16;}
    if(ID == "JLTTB"){return 17;}
    if(ID == "TLTJ-"){return 18;}
    if(ID == "TLTJD"){return 19;}
    if(ID == "TLLL-"){return 20;}
    if(ID == "TLTT-"){return 21;}     
    if(ID == "TLTTP"){return 22;}
    if(ID == "TLTT-"){return 23;}
    if(ID == "TLLTB"){return 24;}
    if(ID == "LJTJ-"){return 25;}
    if(ID == "LJTJD"){return 26;}
    if(ID == "TLLLC"){return 27;}
    else return -1;
}
