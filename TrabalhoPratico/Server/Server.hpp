#pragma once

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>
#include <map>
#include <queue>


#include "Profile.hpp"
#include "Socket.hpp"
#include "Notification.hpp"

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
    

    //Perfis cadastrador no servidor
    map<int, Profile> clients;

    //Notificacoes recebidas pelo servidor
    queue<Notification> receiveByServer;

    //Notificações restantes a serem enviadas
    queue<Notification> toBeSent;

public:

    Server();
    int getLastUuid();
    void setLastUuid();
    string receiveMessage();
    void sendMessage(string message); 
    int setNewClient(string username);
    void registerNewClientSession(int clientUuid);
    bool clientAlreadyExists(string username);
    int getProfileUuid(string username);
    Profile* getProfile(int uuid);
    Socket getConnection();

};
