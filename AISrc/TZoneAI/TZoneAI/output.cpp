#include <iostream>
#include <string>
#include "inout.h"
using namespace std;

void Output::outputFunc(){
    if (tournyStart == true) {
        cout << "JOIN " << tournamentPass << "\n";
        tournyStart = false;
    }
    if (signin == true) {
        cout << "I AM "<< username << " " << passwordUser << "\n";
        signin = false;
    }
    if (makeMove == true){
        cout << "GAME " << game << " MOVE " << moveCount << " PLACE "
        << tile << " AT " << xcoord << ycoord << orientation;
        if(zone >= 0){  //Assuming zone < 0 is considered no tiger placement.
          cout << " TIGER " << zone<< "\n";  //NEED SOMETHING HERE FOR CROCODILES
        } else { cout << " NONE\n";}

        makeMove = false;
    }
}
