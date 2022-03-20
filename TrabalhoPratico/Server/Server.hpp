#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

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


public:

    Server();
    string receiveMessage();


};
