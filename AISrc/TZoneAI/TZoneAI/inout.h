#include <string>
#include <utility>
using namespace std;
class Input{
public:
    //pair<int, int> originCoord;  //xCoord, yCoord (Start Tile)
    //int origOrientation;    //origin orientation
    int score;              //AI' current score
    int opponentScore;      //oppenent's current score
    int moveCount;          //Move #
    char game;              // Game 'A' || 'B'

    bool tournyStart = false;   //lets output know to submit tourney passw
    bool signin = false;        //output should sign in
    //bool origin = false;        //Start Tile, Origin & orientation provided
    bool theTiles = false;
    bool makeMove = false;    //Since we're using Bools to track everything else
    bool noInput = false;

    string startTile;   //Starting Tile.
    string tile;        //top tile
    string tiles;       //list of shuffled tiles

    void takeInput();   //takes in the server input

private:
    int challenges;     //number of challenges in tournament
    int rounds;         //number of rounds per challenge

    string gid;         //game id
    string pid;         //player id
    string rid;         //round id
    int timePlan;       //time to plan before game starts
    int timeMove;       //time to make move
    string message;     //saves input to a string
};

class Output : public Input{
public:
    pair<int, int> coord;   //Replace X & Y Coord
    int orientation;        //either 0, 90, 180, or 270
    int zone;               //where to place tiger in 3x3 grid

    void outputFunc();      //prints all outputs

private:
    string tournamentPass = "cats suck";  //password to get in tournament
    string username = "groupH";        //AI's username
    string passwordUser = "c++ sucks";    //AI's password
};
