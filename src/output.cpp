#include <iostream>
#include <string>
#include <utility>
#include "inout.h"
using namespace std;

Output::Output()
{
  //empty constructor
}

string Output::choosePlacement(int choice)
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
            ret.append(to_string(xcoord));
            ret.append(" ");
            ret.append(to_string(ycoord));
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
            ret.append(to_string(xcoord));
            ret.append(" ");
            ret.append(to_string(ycoord));
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
            ret.append(to_string(xcoord));
            ret.append(" ");
            ret.append(to_string(ycoord));
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
            ret.append(to_string(xcoord));
            ret.append(" ");
            ret.append(to_string(ycoord));

        case 6 :
            ret = "GAME ";
            ret.append(in.gid);
            ret.append(" MOVE ");
            ret.append(to_string(in.moveCount));
            ret.append(" TILE ");
            ret.append(in.tile);
            ret.append(" UNPLACEABLE ADD ANOTHER TIGER TO ");
            ret.append(to_string(xcoord));
            ret.append(" ");
            ret.append(to_string(ycoord));
    }
    
    return 0;  
}

string Output::outputFunc(int x, int y, int orient){
    string ret="";
    xcoord = x;
    ycoord = y; 
    orientation = orient;
    zone = 0;
    ret.append("GAME ");
    ret.push_back(game);
    ret.append(" MOVE ");
    ret.append(to_string(moveCount));
    ret.append(" PLACE ");
    ret.append(tile);
    ret.append(" AT ");
    ret.append(to_string(xcoord));
    ret.append(" ");
    ret.append(to_string(ycoord));
    ret.append(" ");
    ret.append(to_string(orientation));

    if(zone > 0 ){ 
      ret.append(" TIGER "); ret.append(to_string(zone));
    }
    else { 
      ret.append(" NONE");
    }


      /*cout << "GAME " << game << " MOVE " << moveCount << " PLACE "
      << tile << " AT " << xcoord << " " << ycoord << " " << orientation;
      if(zone >= 0){  //Assuming zone < 0 is considered no tiger placement.
        cout << " TIGER " << zone<< "\n";  //NEED SOMETHING HERE FOR CROCODILES
      } else { cout << " NONE\n";}
      makeMove = false;
      cout << ret <<endl;
      
      return ret;
      */
}
