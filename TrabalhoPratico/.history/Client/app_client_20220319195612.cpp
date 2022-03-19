#include <iostream>
#include <string>

//Regex for ip validation
#include <bits/stdc++.h> 

#define ERROR 1

using namespace std;


int main(int argc, char *argv[]) {


    if(argc != 4) {

        cout << "ERROR - The standard input is " + (string)argv[0] + " <profile> <server_adress> <port>!";
        return ERROR;
    }

    string profile = (string)argv[1];

    if(profile.at(0) != '@') {

        cout << "ERROR - Profile must star with '@'!";
        return ERROR;

    }


    int profileLength = profile.length();

    if(profileLength < 4 || profileLength > 20) {

        cout << "ERROR - Profile must contain 4 to 20 characters!";
        return ERROR;
    }


    string serverAdress1 = "172.16.254.1";//(string)argv[1];
    


    regex serverAdress("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0- 9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");


    if(regex_match(serverAdress, serverAdress1)) {

        cout << "igual";

    }


    if()



}