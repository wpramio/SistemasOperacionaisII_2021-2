#include "Server.hpp"
#include "Profile.hpp"

Server::Server() {

    this->lastUuid = 0;
    
    this->commManager = new CommManager(PORT);

    cout << ">> SUCCESS - Server is up on " << " PORT: " << PORT << endl;
    cout << ">> STATUS - Awaiting for clients..." << endl;

}   

string Server::getDateTime() {
    return  ctime(&this->timestamp);
}

void Server::setReceivedByServer(Notification tweetNotify) {
    this->receivedByServer.push(tweetNotify);
}

void Server::setToBeSent(Notification tweetNotify) {
    this->toBeSent.push(tweetNotify);
}

string Server::receiveMessage() {
    
    return this->commManager->receiveMessage();

}

void Server::sendMessage(string message) {

    this->commManager->sendMessage(message);

}

int Server::setNewClient(string username) {

    this->setLastUuid();
    int newUuid = this->getLastUuid();

    Profile newProfile(username, newUuid);
    
    this->clients.insert(pair<int, Profile>(newUuid, newProfile));

    cout << "set new client: " << username << endl;

    // DEBUG
    cout << "current clients:" << endl;
    for(auto it = this->clients.begin(); it != this->clients.end(); ++it) {

        cout << "- " + it->second.getUserName() + " (uuid " + std::to_string(it->first) + ")" << endl;
    }

    return newUuid;

}

int Server::getLastUuid() {
    return this->lastUuid;
}

bool Server::clientAlreadyExists(string username) {

    //Verifica se o usuario já esta registrado no servidor
    for (auto user = this->clients.begin(); user != this->clients.end(); ++user) {
     
        if(user->second.getUserName() == username) {

            return true;
        }

    }

    return false;

}

void Server::registerNewClientSession(int clientUuid) {

    auto item = clients.find(clientUuid);
    item->second.increaseActiveSessions();

    // DEBUG
    string active_sessions = std::to_string(item->second.getActiveSessions());
    cout << "Active sessions for " + item->second.getUserName() + ": " + active_sessions << endl;
    
}

int Server::getProfileUuid(string username) {

    int uuid;

    for (auto user = this->clients.begin(); user != this->clients.end(); ++user) {

        if(user->second.getUserName() == username) {
            uuid = user->second.getUuid();
            break;
        }
    }

    return uuid;

}

void Server::setLastUuid() {

    this->lastUuid += 1;

}

Profile* Server::getProfile(int uuid) {

    auto item = clients.find(uuid);

    return &item->second;

}
