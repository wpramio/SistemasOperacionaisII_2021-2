#include "Server.hpp"
#include "Profile.hpp"

// std::mutex mtx;

Server::Server() {

    this->lastUuid = 0;
    this->newSessionPort = NEW_SESSION_INITIAL_PORT;
    
    this->commManager = new CommManager(MAIN_PORT);

    cout << ">> SUCCESS - Server is up on PORT: " << MAIN_PORT << endl;
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
    
    // mtx.lock();
    string message = this->commManager->receiveMessage();
    // mtx.unlock();

    return message;

}

void Server::sendMessage(string message) {

    // mtx.lock();
    this->commManager->sendMessage(message);
    // mtx.unlock();

}

int Server::setNewClient(string username) {

    this->setLastUuid();
    int newUuid = this->getLastUuid();

    Profile newProfile(username, newUuid);
    
    this->clients.insert(pair<int, Profile>(newUuid, newProfile));

    cout << "set new client: " << username << endl;

    LOG(DEBUG) << "Clientes atuais:";
    for(auto it = this->clients.begin(); it != this->clients.end(); ++it) {

        LOG(DEBUG) << "uuid " << it->first << " - " << it->second.getUserName();
    }

    return newUuid;

}

int Server::getLastUuid() {
    return this->lastUuid;
}

void Server::setLastUuid() {
    this->lastUuid += 1;
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

    string active_sessions = std::to_string(item->second.getActiveSessions());
    LOG(DEBUG) << "Sessoes ativas para " << item->second.getUserName() << ": " << active_sessions;
    
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

Profile* Server::getProfile(int uuid) {

    auto item = clients.find(uuid);

    return &item->second;

}

Profile* Server::getProfileByName(string username) {

    Profile* profile;

    for (auto user = this->clients.begin(); user != this->clients.end(); ++user) {

        if(user->second.getUserName() == username) {
            profile = &user->second;
            break;
        }
    }

    return profile;

}

int Server::getNewSessionPort() {
    return this->newSessionPort;
}

void Server::incrementNewSessionPort() {
    this->newSessionPort++;
}

bool Server::canStartSession(string username) {

    if (this->clientAlreadyExists(username)) {
            
        int clientUuid = this->getProfileUuid(username);
        auto client = this->getProfile(clientUuid);

        // Checa se ja atingiu o numero maximo de sessoes ativas
        if(client->getActiveSessions() >= 2 ) {

            this->sendMessage("There are already 2 active sessions");
            return false;

        }
    }

    return true;

}

void Server::startSession(string username) {

    int clientUuid = this->clientAlreadyExists(username) ? this->getProfileUuid(username) : this->setNewClient(username);

    this->registerNewClientSession(clientUuid);

    thread sessionThread(session, this, username);
    sessionThread.detach();

}

void Server::session(Server* server, string username) {

    cout << ">> New session thread created for " << username << ", listening on port " << server->getNewSessionPort() << endl;

    // CRIACAO SOCKET DA THREAD DE SESSAO
    CommManager commManager(server->getNewSessionPort());

    while(true) {

        string message = commManager.receiveMessage();
        //Pega o comando
        string command = message.substr(0, message.find(":"));
        //Pega o username
        string content = message.substr(message.find(":") + 1);

        if (command == "FOLLOW") {

            // TODO: agrupar num Gerenciador de Perfis

            string myUser = content.substr(0, content.find("::"));
            string toFollow = content.substr(content.find("::") + 2);

            //Recupera os perfis
            Profile *myUserProf = server->getProfileByName(myUser);
            Profile *toFollowProf = server->getProfileByName(toFollow);

            LOG(DEBUG) << myUser << " quer SEGUIR " << toFollow;

            if (!server->clientAlreadyExists(toFollow)) {

                // perfil nao encontrado
                commManager.sendMessage("Profile Not Found");

            // Testa se ja esta seguindo
            } else if (myUserProf->isFollowing(toFollowProf)) {

                commManager.sendMessage("You already follow this profile");

            } else {

                //Adiciona na lista de Seguindo
                myUserProf->setFollowing(toFollowProf);

                //Adiciona na lista de Seguidores do alvo
                toFollowProf->setFollowers(myUserProf);

                commManager.sendMessage("You are now following " + toFollow);

            }

        } else if (command == "SEND") {

            string myUser = content.substr(0, content.find("::"));
            string tweet = content.substr(content.find("::") + 2);

            //Constroi notificacao e guarda no server
            commManager.sendMessage("Tweet posted");


            //Arrumar
           // Notification tweetNotify(myUser, server.getDateTime(), tweet);

            

        } else if (command == "EXIT") {

            int clientUuid;
            clientUuid = server->getProfileUuid(content);
            auto client = server->getProfile(clientUuid);

            cout << "To decrease " << client->getUserName() << endl;

            client->decreaseActiveSessions();

        } else {

            cout << "Error - Invalid command" << endl;
            commManager.sendMessage("Invalid command");
            continue;

        }
    }

}
