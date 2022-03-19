#include <iostream>
#include <string>

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

}