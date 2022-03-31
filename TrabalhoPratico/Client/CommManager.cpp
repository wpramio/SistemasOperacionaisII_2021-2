#include "CommManager.hpp"

// std::mutex mtex;

// Create a socket and set the server address
CommManager::CommManager(string ip, int port) {

    createSocket();

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);              //big endian
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

}

void CommManager::createSocket() {

    /*IPv4, type(UDP), protocol
    Creates an endpoint for communication and returns a file
    descriptor that refers to that endpoint
    */
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketfd < 0) {

        cerr << "!> ERROR - Could not create socket" << endl;
        exit(1);

    }

    cout << ">> SUCCESS - Client socket created" << endl;

}

int CommManager::sendMessage(string message) {

    // mtex.lock();
    int result = sendto(socketfd, message.c_str(), message.length(), 
        0, (const struct sockaddr *) &this->serverAddr, sizeof(this->serverAddr));
    // mtex.unlock();

    LOG(DEBUG) << "sendMessage do Client com msg: " << message;

    return result;

}


int CommManager::receiveMessage() {

	char buffer[MAXLINE];

    // mtex.lock();
    int receiveLen = recvfrom(socketfd, (char *)buffer, MAXLINE, 
        0, (struct sockaddr *) &this->serverAddr,   &this->serverSockLen);
    // mtex.unlock();

    buffer[receiveLen] = '\0';

    this->message = buffer;

    LOG(DEBUG) << "receiveMessage do Client recebeu: " << buffer;
    
    return receiveLen;

}

int CommManager::nonBlockingReceiveMessage() {

	char buffer[MAXLINE];
    int len = sizeof(sockaddr_in);

    // mtex.lock();
    int receiveLen = recvfrom(this->socketfd, buffer, MAXLINE, 
        MSG_DONTWAIT, (struct sockaddr *) &this->serverAddr, (socklen_t*) &len);

    bzero(buffer, MAXLINE);

    // mtex.unlock();

    this->message = buffer;
    
    return receiveLen;

}

string CommManager::getMessage() {
    return this->message;
}
