
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
    
    void clearState();
    bool hasCroc;
    
    
    // lake may have tiger(s) on it
    int num_tigers_p1;                  // increment this num when meeple played
    int num_tigers_p2;
    
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

    

    bool hasDeer;
    bool hasBoar;
    bool hasBuffalo;

    // lake may have tiger(s) on it
    int num_tigers_p1;                  // increment this num when meeple played
    int num_tigers_p2;


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
