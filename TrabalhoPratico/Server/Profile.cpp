#include "Profile.hpp"

Profile::Profile(string username, int uuid) {

    this->uuid = uuid;
    this->username = username;
    this->activeSessions = 0;

}
string Profile::getUserName() {
    return this->username;
}

int Profile::getUuid() {
    return this->uuid;
}



void Profile::pushToFollowers(Profile *followMe) {

    LOG(DEBUG) << username << " tam de Followers antes: " << this->followers.size();

    this->followers.push_back(*followMe);

    LOG(DEBUG) << username << " tam de Followers depois: " << this->followers.size();

}

void Profile::setFollowing(Profile *toFollow) {

    LOG(DEBUG) << "tam de Following antes: " << this->following.size();

    this->following.push_back(*toFollow);

    LOG(DEBUG) << "tam de Following depois: " << this->following.size();

}

int Profile::getActiveSessions() {

    return this->activeSessions;
}

// Incrementa em 1 o numero de sessoes ativas

void Profile::increaseActiveSessions() {

    this->activeSessions++;

}

void Profile::decreaseActiveSessions() {

    this->activeSessions--;

}

bool Profile::isFollowing(Profile *toFollow) {


    for (auto user = this->following.begin(); user != this->following.end(); ++user) {

        if(user->getUserName() == toFollow->getUserName()) {
            return true;
        }

    }

    return false;

}

list<Profile> Profile::getFollowers() {
    return this->followers;
}

int Profile::getFollowersSize() {
    return this->followers.size();
}

queue<Notification> Profile::getReceivedByServer() {
    return this->receivedByServer;
}

queue<Notification> Profile::getToBeSent() {
    return this->toBeSent;
}

int Profile::getReceivedByServerSize() {
    return this->receivedByServer.size();
}

int Profile::getToBeSentSize() {
    return this->toBeSent.size();
}

void Profile::pushToReceivedByServer(Notification tweetNotify) {
    this->receivedByServer.push(tweetNotify);
}

void Profile::pushToBeSent(Notification tweetNotify) {
    this->toBeSent.push(tweetNotify);
}

Notification* Profile::popReceivedByServer() {
    Notification* popped = &this->receivedByServer.front();
    this->receivedByServer.pop();

    return popped;
}

Notification* Profile::popToBeSent() {
    Notification* popped = &this->toBeSent.front();
    this->toBeSent.pop();

    return popped;
}

void Profile::printToBeSent() {

    LOG(DEBUG) << "Bordas do toBeSent do user " << username;
    LOG(DEBUG) << "inicio: " << toBeSent.front().print();
    LOG(DEBUG) << "fim: " << toBeSent.back().print();

}
