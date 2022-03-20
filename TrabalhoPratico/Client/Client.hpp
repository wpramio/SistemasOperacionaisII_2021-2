#include <string>
#include <iostream>
#include <arpa/inet.h>

#define MAXLINE 1024

using namespace std;

class Client {

private: 


    int socketfd;   //socket file descriptor
    struct sockaddr_in serverAddr;
    string message;
    socklen_t len;

public:
    
    Client(string ip, int port);

    int sendMessage(string message);
    int receiveMessage();
    string getMessage();


};