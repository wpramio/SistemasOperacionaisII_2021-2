#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;


class Profile {

private:

    int uuid;
    string username;
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
    void setFollowing(Profile followYou);

};