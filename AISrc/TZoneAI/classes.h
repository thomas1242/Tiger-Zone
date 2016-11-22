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
    
    static bool tournyStart;   //lets output know to submit tourney passw
    bool signin = false;        //output should sign in
    
    string tile;        //top tile
    string tiles;       //list of shuffled tiles
    
    Input();
    ~Input();
    
private:
    int challenges;     //number of challenges in tournament
    int rounds;         //number of rounds per challenge
    
    string gid;         //game id
    string pid;         //player id
    string rid;         //round id
    string timePlan;    //time to plan before game starts
    string timeMove;    //time to make move
    string inputString; //saves string input
    
    void takeInput();   //takes in the server input
    
};

class Output{
public:
    int xcoord;             //x coordinate for tile placement
    int ycoord;             //y coordinate for tile placement
    int orientation;        //either 0, 90, 180, or 270
    int zone;               //where to place tiger in 3x3 grid
    
private:
    string tournamentPass = "cats suck";  //password to get in tournament
    string username;        //AI's username
    string passwordUser;    //AI's password
    
    void outputFunc();      //prints all outputs
    
};

#endif /* Header_h */
