#include "Client.hpp"

//Constructor
Client::Client(string ip, int port) {

    /*IPv4, type(UDP), protocol
    Creates an endpoint for communication and returns a file
    descriptor that refers to that endpoint
    */
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketfd < 0) {

        cout << "!> ERROR - Could not create socket";
        exit(1);

    }

    cout << ">> SUCCESS - Socket client created" << endl;

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    this->serverAddr.sin_port = htons(port); //big endian
    
    this->len = sizeof(this->serverAddr); // len is value/resuslt

}

int Client::sendMessage(string message) {

    int sendtoReturn;
    
    sendtoReturn = sendto(socketfd, (const char *)message.c_str(), message.length(),
        MSG_CONFIRM, (const struct sockaddr *)&this->serverAddr,
        this->len);

    return sendtoReturn;

}

int Client::receiveMessage() {

    char buffer[MAXLINE];

    //MUTEX

    int receiveLen = recvfrom(socketfd, (char *)buffer, MAXLINE, 
        MSG_WAITALL, (struct sockaddr *) &this->serverAddr,
        &len);

    buffer[receiveLen] = '\0';

    this->message = buffer;
    

    return receiveLen;

}


string Client::getMessage() {
    return this->message;
}