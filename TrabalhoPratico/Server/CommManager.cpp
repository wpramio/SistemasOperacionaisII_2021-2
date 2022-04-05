#include "CommManager.hpp"


// Create a socket and bind it to 0.0.0.0
CommManager::CommManager(int port) {
    
    createSocket();

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);              // big endian
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // big endian

    // Bind - unique local name to the socket with descriptor socket
    if (bind(this->socketfd, (struct sockaddr *)&serverAddr, sizeof(this->serverAddr)) < 0) {

        cerr << "!> ERROR - Binding error" << endl;
        exit(1);
    }

    this->clientSockLen = sizeof(this->clientAddr);
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

    cout << ">> SUCCESS - Server socket created" << endl;

}

void CommManager::sendMessage(string message) {

    sendto(socketfd, message.c_str(), message.length() + 1, 
        MSG_CONFIRM, (const struct sockaddr *) &this->clientAddr, this->clientSockLen);

    LOG(DEBUG) << "sendMessage do Server com msg: " << message;

}


string CommManager::receiveMessage() {

	char buffer[MAXLINE];
    int receiveLen;

    receiveLen = recvfrom(socketfd, (char *)buffer, MAXLINE, 
        0, (struct sockaddr *) &this->clientAddr,   &this->clientSockLen);

    if(receiveLen < 0) {
        
        cerr << "!> SERVER - Error receiving message";
        exit(1);
    }

    buffer[receiveLen] = '\0';

    LOG(DEBUG) << "receiveMessage do Server recebeu: " << buffer;
    
    return buffer;

}
