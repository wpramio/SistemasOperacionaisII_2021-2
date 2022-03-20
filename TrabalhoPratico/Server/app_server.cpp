#include "Server.hpp"

int main() {


    Server server;

    while(true) {
        string message = server.receiveMessage();
        cout << message << endl;
    }
    

    return 0;
}