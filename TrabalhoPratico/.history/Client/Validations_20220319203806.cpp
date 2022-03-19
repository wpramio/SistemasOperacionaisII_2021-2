
#define ERROR 1
#define IPV4_REGEX "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"
#define PORT_REGEX "^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])"


class Validations {

public:

    bool validateIPv4(string serverAdress) {

    regex ipv4(IPV4_REGEX);
 
    if( not regex_match(serverAdress, ipv4)) {
        cerr << "ERROR - Invalid IPv4 adress. Use xxx.xxx.xxx.xx";
        return ERROR;
    }


    }

    bool validatePort() {



    }


}