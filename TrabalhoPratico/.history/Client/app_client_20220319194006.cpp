#include <iostream>
#include <string>

using namespace std;


int main(int argc, char *argv[]) {


    if(argc != 4) {

        cout << "ERROR - The standard input is " + (string)argv[0] + " <profile> <server_adress> <port>!";
        return 1;
    }

}