#include "Profile.hpp"

string Profile::getUserName() {
    return this->username;
}

int Profile::getUuid() {
    return this->uuid;
}


Profile::Profile(string username, int uuid) {

    this->uuid = uuid;
    this->username = username;
    this->activeSessions = 0;

}

void Profile::setFollowers(Profile followMe) {

    this->followers.push_back(followMe);


}

void Profile::setFollowing(Profile followYou) {

    this->following.push_back(followYou);

}

int Profile::getActiveSessions() {

    return this->activeSessions;
}

//Retorna true se é possivel criar uma nova sessao
//False, caso contrario

bool Profile::setActiveSession() {

    if(getActiveSessions() < 2) {

        this->activeSessions++;

        return true;
    
    }
    cout << endl << this->activeSessions << endl;

    return false;

}