#pragma once
#include <iostream>
#include <string>
#include <list>

#include "Socket.hpp"

using namespace std;


class Profile {

private:

    int uuid;
    string username;

    list<Profile> followers;
    list<Profile> following;
    //Nao sei se isso ta certo
    int activeSessions;


public: 
    
    Profile(string username, int uuid);
    string getUserName();
    int getUuid();
    int getActiveSessions();
    bool setActiveSession();
    void setFollowers(Profile *followMe);
    void setFollowing(Profile *toFollow, Socket sock);
    bool followingAlreadyExists(Profile myUser, string toFollowUserName);

    bool isFollowing(Profile *toFollow);

};