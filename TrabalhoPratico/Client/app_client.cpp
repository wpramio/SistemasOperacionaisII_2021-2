#include <iostream>
#include <string>
#include "Validations.hpp"
#include "ClientSession.hpp"


using namespace std;


int main(int argc, char *argv[]) {

    Validations validations;
    string profile = (string)argv[1];
    string ip = (string)argv[2]; //UPD uses IPv4
    string portStr = (string) argv[3];

    if(not validations.validateArguments(argc)) {
        return 1;
    }

    //IP validation
    if(not validations.validateIPv4(ip)) {
        return 1;
    }

    //Port Validation
    if(not validations.validatePort(portStr))  {
        return 1;
    }

    ClientSession clientSession(profile, ip, portStr);
}