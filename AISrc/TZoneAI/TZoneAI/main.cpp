//
//  main.cpp
//  TZoneAI
//
//  Created by Evan Amstutz on 11/23/16.
//  Copyright © 2016 Evan Amstutz. All rights reserved.
//

#include <iostream>
#include <string>
#include "inout.h"
using namespace std;

int main(void){
    Output output;
    while (output.noInput == false) {
        output.takeInput();
        output.outputFunc();
    }
    return 0;
}
