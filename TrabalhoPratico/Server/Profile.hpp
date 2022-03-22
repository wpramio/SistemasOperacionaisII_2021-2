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

    //Nao sei se isso ta certo
    list<Profile> followers;
    list<Profile> following;
    int activeSessions;


public: 

    Profile(string username, int uuid);
    string getUserName();
    int getUuid();
    int getActiveSessions();
    bool setActiveSession();
    void setFollowers(Profile followMe);
    void setFollowing(Profile followYou, Socket sock);

};