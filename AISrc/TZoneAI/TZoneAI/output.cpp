//
//  output.cpp
//  TZoneAI
//
//  Created by Evan Amstutz on 11/22/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//


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
}
