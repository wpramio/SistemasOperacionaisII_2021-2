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

void Profile::setActiveSession() {
    this->activeSessions++;
}