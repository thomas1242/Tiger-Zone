//
//  Header.h
//  TZoneAI
//
//  Created by Evan Amstutz on 11/22/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <string>
using namespace std;
class Input{
public:
    int score;          //AI' current score
    int opponentScore;  //oppenent's current score
    
    bool tournyStart = false;   //lets output know to submit tourney passw
    bool signin = false;        //output should sign in
    bool noInput = false;
    
    string tile;        //top tile
    string tiles;       //list of shuffled tiles
    
    void takeInput();   //takes in the server input
    
private:
    int challenges;     //number of challenges in tournament
    int rounds;         //number of rounds per challenge
    
    string gid;         //game id
    string pid;         //player id
    string rid;         //round id
    string timePlan;    //time to plan before game starts
    string timeMove;    //time to make move
    string message;     //saves input to a string
};

class Output : public Input{
public:
    int xcoord;             //x coordinate for tile placement
    int ycoord;             //y coordinate for tile placement
    int orientation;        //either 0, 90, 180, or 270
    int zone;               //where to place tiger in 3x3 grid
    
    void outputFunc();      //prints all outputs
    
private:
    string tournamentPass = "cats suck";  //password to get in tournament
    string username = "groupH";        //AI's username
    string passwordUser = "c++ sucks";    //AI's password
};


#endif /* Header_h */
