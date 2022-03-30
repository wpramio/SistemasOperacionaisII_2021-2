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

};