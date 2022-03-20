#include <string>
#include <iostream>
#include <arpa/inet.h>

using namespace std;

class Client {

private: 

    int socketfd;   //socket file descriptor
    struct sockaddr_in serverAddr;
    string message;

public:
    
    Client(string message, int port);

    int sendMessage(string message);
    int receiveMessage();


};