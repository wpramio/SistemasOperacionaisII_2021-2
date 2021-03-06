#include <string>
#include <string.h> //For bzero
#include <iostream>
#include <arpa/inet.h>
#include <mutex>
#include "../shared/Logger.hpp"

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
    int nonBlockingReceiveMessage(); 
    int receiveMessage();
    string getMessage();


};