#include "Validations.hpp"

bool Validations::validateArguments(int argc) {

    if(argc != 4) {
        cerr << "ERROR - The standard input is ./app_client <profile> <server_adress> <port>!";
        return ERROR;
    }

    return true;

}


bool Validations::validateProfile(string profile) {

    if(profile.at(0) != '@') {
        cerr << "ERROR - Profile must star with '@'";
        return ERROR;
    }

    int profileLength = profile.length();

    if(profileLength < 4 || profileLength > 20) {
        cerr << "ERROR - Profile must contain 4 to 20 characters";
        return ERROR;
    }

    return true;
}

bool Validations::validateIPv4(string serverAdress) {

    regex ipv4(IPV4_REGEX);

    if( not regex_match(serverAdress, ipv4)) {
        cerr << "ERROR - Invalid IPv4 adress. Use xxx.xxx.xxx.xx";
        return ERROR;
    }

    return true;
}

bool Validations::validatePort(string port) {

    regex portRegex(PORT_REGEX);

    if(not regex_match(port, portRegex)) {
        cerr << "ERROR - Invalid Port. Use a number between 0 and 65535";
        return ERROR;
    }

    return true;

}


