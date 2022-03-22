#include "Server.hpp"
#include "Profile.hpp"

std::mutex mtx;

Server::Server()
{
    this->lastUuid = 0;
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    char buffer[MAXLINE];

    if (this->socketfd < 0)
    {

        cout << " !> ERROR - Could not create socket";
        exit(1);
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(PORT);              // big endian
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // big endian

    cout << ">> SUCCESS - Socket created" << endl;

    // Bind - unique local name to the socket with descriptor socket
    if (bind(this->socketfd, (struct sockaddr *)&serverAddr, sizeof(this->serverAddr)) < 0)
    {

        cout << "!> ERROR - Binding error";
        exit(1);
    }

    cout << ">> SUCCESS - Server is up on " << " PORT: " << PORT << endl;
    cout << ">> STATUS - Awaiting for clients..." << endl;

    socklen_t len;
    this->len = sizeof(this->clientAddr); 

}   

string Server::receiveMessage() {
    
    char buffer[MAXLINE];

    //MUTEX

    int receiveLen = recvfrom(socketfd, (char *)buffer, MAXLINE, 
        0, (struct sockaddr *) &this->clientAddr,   &this->len);

    if(receiveLen < 0) {
        
        cout << "!> SERVER - Error receiving message";
        exit(1);
    }

    buffer[receiveLen] = '\0';
    
    return buffer;

}

void Server::sendMessage(string message) {

    mtx.lock();
    sendto(socketfd, message.c_str(), message.length(), 
        MSG_CONFIRM, (const struct sockaddr *) &this->clientAddr, this->len);
    mtx.unlock();
}

int Server::setNewClient(string username) {

    int newUuid = this->getLastUuid() + 1;

    Profile newProfile(username, newUuid);

    this->clients.insert(pair<int, Profile>(newUuid, newProfile));

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

bool Server::startClientSession(int clientUuid) {

    auto item = clients.find(clientUuid);
    item->second.setActiveSession();

    return true;
    
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

Profile Server::getProfile(int uuid) {

    auto item = clients.find(uuid);
    return item->second;

}

Socket Server::getConnection() {
	return Socket(this->socketfd, this->clientAddr);
}