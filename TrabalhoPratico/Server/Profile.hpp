#pragma once
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include "../shared/Logger.hpp"

#include "Notification.hpp"

using namespace std;


class Profile {

private:

    int uuid;
    string username;

    list<Profile*> followers = {};

    // Notificacoes recebidas a partir desse Profile 
    queue<Notification> receivedByServer = {};

    // Notificações pendentes a serem enviadas a este Profile
    queue<Notification> toBeSent = {};

    //Nao sei se isso ta certo
    int activeSessions;


public: 

    Profile(string username, int uuid);
    string getUserName();
    int getUuid();
    int getActiveSessions();
    void increaseActiveSessions();
    void decreaseActiveSessions();
    void pushToFollowers(Profile *followMe);
    bool isFollowedBy(Profile *profile);
    list<Profile*> getFollowers();
    int getFollowersSize();

    queue<Notification> getReceivedByServer();
    queue<Notification> getToBeSent();
    int getReceivedByServerSize();
    int getToBeSentSize();
    void pushToReceivedByServer(Notification tweetNotify);
    void pushToBeSent(Notification tweetNotify);
    Notification* popReceivedByServer();
    Notification* popToBeSent();
    void printToBeSent();

};