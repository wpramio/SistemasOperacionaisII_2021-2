#include <iostream>
#include <string>
#include "Validations.hpp"


using namespace std;


int main(int argc, char *argv[]) {

    Validations validations = new Validations;
    string profile = (string)argv[1];
    string serverAddress = (string)argv[2];
    string portStr = (string) argv[3];

    if( not validations.validateArguments()) {
        return 1;
    }

    //IP validation
    if( not validations.validateIPv4(serverAddress) ) {
        return 1;
    }

    //Port Validation
    if( not validations.validatePort(portStr)  {
        return 1;
    }

    int port = stoi(portStr);

       
}