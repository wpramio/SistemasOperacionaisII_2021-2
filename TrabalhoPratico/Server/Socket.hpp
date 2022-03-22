#pragma once

#include <arpa/inet.h>
#include <string>

#define MAXLINE 1024

using namespace std;

class Socket {


private:

    int connSocket;
    struct sockaddr_in connAddr;
    string message;

public:

    Socket();
    Socket(int sock, struct sockaddr_in);
    int sendMessage(string message);
    int receiveMessage();
    string getMessage();
    string getAddress();
    int getPort();
    

};