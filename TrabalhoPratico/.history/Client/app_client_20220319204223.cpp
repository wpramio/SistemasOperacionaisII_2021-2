#include <iostream>
#include <string>
#include "Validations.hpp"


using namespace std;


int main(int argc, char *argv[]) {


    if(argc != 4) {
        cerr << "ERROR - The standard input is " + (string)argv[0] + " <profile> <server_adress> <port>!";
        return ERROR;
    }


    Validations validations = new Validations;


    string profile = (string)argv[1];

    if(profile.at(0) != '@') {
        cerr << "ERROR - Profile must star with '@'";
        return ERROR;
    }




    int profileLength = profile.length();

    if(profileLength < 4 || profileLength > 20) {
        cerr << "ERROR - Profile must contain 4 to 20 characters";
        return ERROR;
    }


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