#include <iostream>
#include <string>
#include "Validations.hpp"


using namespace std;


int main(int argc, char *argv[]) {

    Validations validations = new Validations;

    if( not validations.validateArguments()) {
        return 1;
    }




    string profile = (string)argv[1];


    //IP validation
    string serverAddress = (string)argv[2];

    if( not validations.validateIPv4(serverAddress)) {
        return 1;
    }

    //Port Validation
    if( not validations.validatePort(portStr)) {
        return 1;
    }

    int port = stoi(portStr);

       
}