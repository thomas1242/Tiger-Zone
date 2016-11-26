#include <iostream>
#include <string>
#include "inout.h"
using namespace std;
//Until we have a makefile - to compile:
//g++ -std=c++11 inout.h input.cpp output.cpp main.cpp

int main(void){
    Output output;
    while (output.noInput == false) {
        output.takeInput();
        output.outputFunc();
    }
    return 0;
}
