//
//  output.cpp
//  TZoneAI
//
//  Created by Evan Amstutz on 11/22/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//


#include <iostream>
#include <string>
#include "AIclasses.h"
using namespace std;

void Output::outputFunc(){
    if (Input::returnBools() == true) {
        cout << "JOIN" << tournamentPass;
    }
}
