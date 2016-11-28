#include <string>
using namespace std;
class Input{
public:

    int score;          //AI' current score
    int opponentScore;  //oppenent's current score
    int moveCount;      //Move #
    char game;          // Game 'A' || 'B'

    bool tournyOpen = false;   //lets output know to submit tourney passw
    bool challengeOpen = false;        //output should sign in
    bool makeMove = false;    //Since we're using Bools to track everything else
    bool gameOpen = false;

    string startTile;    //Starting Tile
    string tile;        //top tile
    string tiles;       //list of shuffled tiles
    string gid;         //game id




    Input();
    void takeInput(string message);   //takes in the server input

private:
    int challenges;     //number of challenges in tournament
    int rounds;         //number of rounds per challenge

    string pid;         //player id
    string rid;         //round id
    int timePlan;       //time to plan before game starts
    int timeMove;       //time to make move
    string message;     //saves input to a string
};

class Output : public Input{
public:
    int xcoord;
    int ycoord;
    int orientation;        //either 0, 90, 180, or 270
    int zone;               //where to place tiger in 3x3 grid

    Output();
    string outputFunc(int x, int y, int orient);        //prints all outputs
    string choosePlacement(int choice);      //switch statement for client messages

private:
    string tournamentPass = "cats suck";  //password to get in tournament
    string username = "groupH";        //AI's username
    string passwordUser = "c++ sucks";    //AI's password
};
