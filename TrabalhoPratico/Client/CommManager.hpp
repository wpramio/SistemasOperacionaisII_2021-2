#pragma once

#include <string>
#include <string.h> //For bzero
#include <iostream>
#include <arpa/inet.h>
#include <mutex>
#include "../shared/Logger.hpp"

#define MAXLINE 1024

using namespace std;

class CommManager {

private:

    int socketfd;
    struct sockaddr_in serverAddr;
    socklen_t serverSockLen;
    string message;

    void createSocket();

public:

    CommManager(string ip, int port);
    int sendMessage(string message);
    int nonBlockingReceiveMessage();
    int receiveMessage();
    string getMessage();

};