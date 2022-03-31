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
#include <thread>


#include "Profile.hpp"
#include "Notification.hpp"
#include "CommManager.hpp"

#define MAIN_PORT 8888
#define NEW_SESSION_INITIAL_PORT 9000
#define MAXLINE 1024

using namespace std;

class Server {

private:

    int lastUuid;
    std::time_t timestamp;
    int newSessionPort;

    CommManager* commManager;

    //Perfis cadastrados no servidor
    map<int, Profile> clients;

    //Notificacoes recebidas pelo servidor
    queue<Notification> receivedByServer;

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
    Profile* getProfileByName(string username);
    string getDateTime();
    void setReceivedByServer(Notification tweetNotify);
    void setToBeSent(Notification tweetNotify);

    int getNewSessionPort();
    void incrementNewSessionPort();
    bool canStartSession(string username);
    void startSession(string username);

    //Static for using in threads
    static void session(Server* server, string username);

};
