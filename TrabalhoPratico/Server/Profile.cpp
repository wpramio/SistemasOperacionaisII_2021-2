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

void Profile::setFollowing(Profile toFollow, Socket sock) {


    //Testar se já não esta seguindo
    for (auto user = this->following.begin(); user != this->following.end(); ++user) {

       if(user->getUserName() == toFollow.getUserName()) {
           //Já segue
           
           return;
       }

    }

    //Nao sei se isso ta certo
    this->following.push_back(toFollow);

    sock.sendMessage("Following " + toFollow.getUserName());

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