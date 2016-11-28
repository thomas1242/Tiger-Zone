#include <iostream>
#include <string>
#include "inout.h"

using namespace std;

class Decision : public Board{
public:

    bool lakeNotOwnedAvailable;
    bool trailNotOwnedAvailable;
    bool lakeClaimed;
    bool trailClaimed;
    
    int makeDecision(int cardID);
};
