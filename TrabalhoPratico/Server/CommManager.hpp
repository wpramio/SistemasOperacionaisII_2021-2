#pragma once

#include <arpa/inet.h>
#include <string>
#include <mutex>
#include <iostream>
#include "../shared/Logger.hpp"

#define MAXLINE 1024

using namespace std;

class CommManager {

private:

    int socketfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientSockLen;

    void createSocket();

public:

    CommManager(int port);
    void sendMessage(string message);
    string receiveMessage();

};