//
//  output.cpp
//  TZoneAI
//
//  Created by Evan Amstutz on 11/22/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//


#include <iostream>
#include <string>
#include "classes.h"
using namespace std;

void Output::outputFunc(){
    if (Input::tournyStart == true) {
        cout << "JOIN" << tournamentPass;
    }
}
