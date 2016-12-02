#include <iostream>
#include <string>
#include <utility>
#include "inout.h"
#include <sstream>
using namespace std;

Output::Output()
{
  //empty constructor
}

void Output::choosePlacement(int choice)
{
    Input in;
    string ret = "";
    switch(choice)
    {
        case 1 : 
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" PLACE ");
            ret.append(in.tile);
            ret.append(" AT ");
            ret.append(to_string(coord.first));
            ret.append(" ");
            ret.append(to_string(coord.second));
            ret.append(" ");
            ret.append(to_string(orientation)); 
            ret.append(" NONE");

        case 2 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" PLACE ");
            ret.append(in.tile);
            ret.append(" AT ");
            ret.append(to_string(coord.first));
            ret.append(" ");
            ret.append(to_string(coord.second));
            ret.append(" ");
            ret.append(to_string(orientation)); 
            ret.append(" CROCODILE");

        case 3 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" PLACE ");
            ret.append(in.tile);
            ret.append(" AT ");
            ret.append(to_string(coord.first));
            ret.append(" ");
            ret.append(to_string(coord.second));
            ret.append(" ");
            ret.append(to_string(orientation)); 
            ret.append(" TIGER ");
            ret.append(to_string(zone));

        case 4 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" TILE ");
            ret.append(in.tile);
            ret.append(" UNPLACEABLE PASS");
       
        case 5 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" TILE ");
            ret.append(in.tile);
            ret.append(" UNPLACEABLE RETRIEVE TIGER AT ");
            ret.append(to_string(coord.first));
            ret.append(" ");
            ret.append(to_string(coord.second));

        case 6 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" TILE ");
            ret.append(in.tile);
            ret.append(" UNPLACEABLE ADD ANOTHER TIGER TO ");
            ret.append(to_string(coord.first));
            ret.append(" ");
            ret.append(to_string(coord.second));
    }
}

void Output::outputFunc(int x, int y, int orient, string game, string tile){
    string ret="";
    coord = make_pair(x, y);
    orientation = orient;
    zone = 0;
    ret.append("GAME");
    ret.append(game);
    ret.append(" MOVE ");
    cout << "Inside Output, moveCount: " << ++moveCount << endl;
    ret.append(to_string(moveCount));
    if(moveCount > 2)
    {
        ret.append(" PLACE");
    }
    else
    {
        ret.append(" PLACE ");
    }
    
    ret.append(tile);
    ret.append(" AT ");
    ret.append(to_string(coord.first));
    ret.append(" ");
    ret.append(to_string(coord.second));
    ret.append(" ");
    ret.append(to_string(orientation));

    if(zone > 0 ){ 
      ret.append(" TIGER "); ret.append(to_string(zone));
    }
    else { 
      ret.append(" NONE");
    }
    outMessage = ret;
}
