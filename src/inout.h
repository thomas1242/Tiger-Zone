#include <string>
using namespace std;
class Input{
public:

    int score;          //AI' current score
    int opponentScore;  //oppenent's current score
    int moveCount;      //Move #
    string initGame;
    //string game;          // Game 'A' || 'B'
    pair<int,int> originCoord;
    int origOrientation;    //Origin orientation
    pair<int, int> coord;   //Replace X & Y Coord

    bool tiger=false;   //placing tiger
    bool croc=false;    //placing croc
    bool forfeit = false;
    bool tournyOpen = false;   //lets output know to submit tourney passw
    bool signin = false;        //output should sign in
    bool makeMove = false;    //Since we're using Bools to track everything else
    bool noInput = false;
    bool tournyStart = false;
    bool challengeOpen = false;
    bool gameOpen = false;
    int cid;            //challenge id
    int rid;             //round id

    string startTile;    //Starting Tile
    string tile;        //top tile
    string tiles;       //list of shuffled tiles
    string gid;         //game id
    string pid;         //player id

    int orientation;
    int zone;
    Input();
    void takeInput(string message);   //takes in the server input
    int convertID(string tile);
    int rounds;         //number of rounds per challenge    
    
private:
    int challenges;     //number of challenges in tournament
    int timePlan;       //time to plan before game starts
    int timeMove;       //time to make move
};

class Output : public Input{
public:
    Output();
    void outputFunc(int x, int y, int orient, string game, string tile);        //prints all outputs
    void choosePlacement(int choice);      //switch statement for client messages
    string outMessage;     //saves input to a string


};
