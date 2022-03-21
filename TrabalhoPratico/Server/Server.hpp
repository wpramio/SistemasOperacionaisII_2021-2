#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "Profile.hpp"
#include <map>

#define PORT 8888
#define MAXLINE 1024

using namespace std;

class Server {

private:

    int socketfd;   //Socket file descriptor
    int server;
    struct sockaddr_in serverAddr;   
    struct sockaddr_in clientAddr;
    socklen_t len; 
    int lastUuid;
    
    map<int, Profile> clients;


public:

    Server();
    int getLastUuid();
    string receiveMessage();
    void sendMessage(string message); 
    void setNewClient(string username);
    bool startClientSession();
    bool clientAlreadyExists(string username);
    


};
