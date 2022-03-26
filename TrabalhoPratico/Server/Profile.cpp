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



void Profile::setFollowers(Profile *followMe) {

    if(followMe->isFollowing(this)) {
        return;    
    }

    this->followers.push_back(*followMe);


}

void Profile::setFollowing(Profile *toFollow, Socket sock) {

    //Testar se já não esta seguindo
    cout << " N " << this->following.size() << endl;

    if(this->isFollowing(toFollow)) {
        sock.sendMessage("You already follows this profile");
        return;
    }

    this->following.push_back(*toFollow);
    cout << " N2 " << this->following.size() << endl;

    sock.sendMessage("Following " + toFollow->getUserName());
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

bool Profile::followingAlreadyExists(Profile myUser, string toFollowUserName) {

    //Verifica se o usuario já esta registrado no servidor
    for (auto user = this->following.begin(); user != this->following.end(); ++user) {
        
        cout << user->getUserName() << endl;
        if(user->getUserName() == toFollowUserName) {
            return true;
        }

    }

    return false;


}

bool Profile::isFollowing(Profile *toFollow) {


    for (auto user = this->following.begin(); user != this->following.end(); ++user) {

        if(user->getUserName() == toFollow->getUserName()) {
            return true;
        }

    }

    return false;

}