#include <iostream>
#include <string>

//Regex for ip validation
#include <bits/stdc++.h>

#define ERROR 1
#define REGEX_IPV4 "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"

using namespace std;


int main(int argc, char *argv[]) {


    if(argc != 4) {
        cerr << "ERROR - The standard input is " + (string)argv[0] + " <profile> <server_adress> <port>!";
        return ERROR;
    }

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
    string serverAddressInformed = (string)argv[2];
    regex ipv4(REGEX_IPV4);
 
    if( not regex_match(serverAddressInformed, ipv4)) {
        cerr << "ERROR - Invalid IPv4 adress. Use xxx.xxx.xxx.xx";
        return ERROR;
    }

    //Port validation
    regex portRegex("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])");
    string port = (string)argv[3];

    if(not regex_match()) {



    }


    
       
    


}