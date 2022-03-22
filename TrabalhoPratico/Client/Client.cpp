#include "Client.hpp"

std::mutex mtx;

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
    
    sendtoReturn = sendto(this->socketfd, message.c_str(), message.length(),
        0, (const struct sockaddr *)&this->serverAddr,
        sizeof(this->serverAddr));


    return sendtoReturn;

}

int Client::receiveMessage() {

    char buffer[MAXLINE];

    //Checar se precisa
    //lock guard garante que o processo nao fique bloqueado
    mtx.lock();

    int receiveLen = recvfrom(this->socketfd, (char *)buffer, MAXLINE, 
        0, (struct sockaddr *) &this->serverAddr,
        &len);

    mtx.unlock();

    buffer[receiveLen] = '\0';

    this->message = buffer;

    return receiveLen;

}


int Client::nonBlockingReceiveMessage() {
    
	char buffer[MAXLINE];
	int len = sizeof(sockaddr_in);

	mtx.lock();

	 int receiveLen = recvfrom(this->socketfd, buffer, MAXLINE, 
        MSG_DONTWAIT, (struct sockaddr *) &this->serverAddr, (socklen_t*) &len);
    
    bzero(buffer, MAXLINE);

    mtx.unlock();

    this->message = buffer;

	return receiveLen;
}


string Client::getMessage() {
    return this->message;
}