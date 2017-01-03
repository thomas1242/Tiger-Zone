
#ifndef regs_h
#define regs_h
#include <vector>
using namespace std;

class Trail {
    
public:
    Trail();
    ~Trail();
    void setId(int id);
    int getId();
    int edgeConnects;   // number of edge connections
    int getOwner();    // returns which player owns the regions, if any
    void addMeeple(int playerID);
    bool isComplete();
    int preyCount;
    int numTiles;
    bool hasMeeple();

    void clearState();
    bool hasCroc;
    bool isCompleted = false;
    
    // lake may have tiger(s) on it
    int num_tigers_p1;                  // increment this num when meeple played
    int num_tigers_p2;
    bool hasGoat;
    
private:
    int id;
};

//=====================================================

class Lake {
    
public:
    Lake();
    ~Lake();
    void setId(int id);
    int getId();
    int edgeConnects;   // number of edge connections
    int getOwner();    // returns which player owns the regions, if any
    void addMeeple(int playerID);
    bool isComplete();
    int preyCount;
    int numTiles;
    bool hasCroc;
    void clearState();
    bool hasMeeple();
    bool isCompleted = false;


    bool hasDeer;
    bool hasBoar;
    bool hasBuffalo;
    bool hasGoat;

    // lake may have tiger(s) on it
    int num_tigers_p1;                  // increment this num when meeple played
    int num_tigers_p2;
    bool hasMeep;

private:
    int id;			// which jungle is this
    
};

//=====================================================


class Jungle {
    
public:
    Jungle();
    ~Jungle();
    void setId(int id);
    int getId();
    int edgeConnects;   // number of edge connections
    int getOwner();    // returns which player owns the regions, if any
    void addMeeple(int playerID);
    bool isComplete();
    int preyCount;
    int numTiles;
    void clearState();

    // lake may have tiger(s) on it
    int num_tigers_p1;                  // increment this num when meeple played
    int num_tigers_p2;
    
    vector<int> adjacentLakeIDs;
    
private:
    int id;			// which jungle is this
    
};






#endif /* Header_h */
