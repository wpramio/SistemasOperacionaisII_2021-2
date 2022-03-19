#include "Validations.hpp"

bool validateIPv4(string serverAdress) {

    regex ipv4(IPV4_REGEX);

    if( not regex_match(serverAdress, ipv4)) {
        cerr << "ERROR - Invalid IPv4 adress. Use xxx.xxx.xxx.xx";
        return ERROR;
    }

    return true;




}

bool validatePort() {



}


