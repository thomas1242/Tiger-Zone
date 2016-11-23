//
//  main.cpp
//  TZoneAI
//
//  Created by Evan Amstutz on 11/22/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//

#include <iostream>
#include <string>
#include "inout.h"
using namespace std;


void Input::takeInput(){
    
    getline(cin, message);
    
    
        
    if(message == "THIS IS SPARTA!"){
        tournyStart = true;
        message = "";
    }
    
    if(message == "HELLO!") {
        signin = true;
        message = "";
    }
    
    if (message == "END OF CHALLENGES") {
        noInput = true;
    }
    
}
