#include "Validations.hpp"

bool Validations::validateIPv4(string serverAdress) {

    regex ipv4(IPV4_REGEX);

    if( not regex_match(serverAdress, ipv4)) {
        cerr << "ERROR - Invalid IPv4 adress. Use xxx.xxx.xxx.xx";
        return ERROR;
    }

    return true;
}

bool Validations::validatePort() {

    regex portRegex(PORT_REGEX);
    string portStr= (string)argv[3];

    if(not regex_match(portStr, portRegex)) {
        cerr << "ERROR - Invalid Port. Use a number between 0 and 65535";
        return ERROR;
    }

}


