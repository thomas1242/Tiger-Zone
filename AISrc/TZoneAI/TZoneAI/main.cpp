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
