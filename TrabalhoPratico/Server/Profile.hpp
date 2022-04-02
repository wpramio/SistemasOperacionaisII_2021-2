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

    list<Profile> followers;
    list<Profile> following;

    // Notificacoes recebidas a partir desse Profile 
    queue<Notification> receivedByServer;

    // Notificações pendentes a serem enviadas a este Profile
    queue<Notification> toBeSent;

    //Nao sei se isso ta certo
    int activeSessions;


public: 
    
    Profile(string username, int uuid);
    string getUserName();
    int getUuid();
    int getActiveSessions();
    void increaseActiveSessions();
    void decreaseActiveSessions();
    void setFollowers(Profile *followMe);
    void setFollowing(Profile *toFollow);
    bool isFollowing(Profile *toFollow);
    list<Profile> getFollowers();
    int getFollowersSize();

    queue<Notification> getReceivedByServer();
    queue<Notification> getToBeSent();
    int getReceivedByServerSize();
    int getToBeSentSize();
    void pushToReceivedByServer(Notification tweetNotify);
    void pushToBeSent(Notification tweetNotify);

};