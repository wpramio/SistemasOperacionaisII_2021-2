#include "Socket.hpp"


Socket::Socket() {
    
}

//Constructor
Socket::Socket(int sock, struct sockaddr_in connAddr) {

    this->connSocket = sock;
    this->connAddr = connAddr;

}


int Socket::sendMessage(string message) {
    return sendto(this->connSocket, message.c_str(), message.length(), 0, (sockaddr*) &this->connAddr, sizeof(this->connAddr));
}


int Socket::receiveMessage() {
	char buffer[MAXLINE];
	int recvLen, addrLen = sizeof(this->connAddr);

	recvLen = recvfrom(this->connSocket, buffer, MAXLINE, 0, (sockaddr*) &this->connAddr, (socklen_t*) &addrLen);
    this->message = buffer;

	return recvLen;
}

string Socket::getMessage() {
    return this->message;
}

string Socket::getAddress() {
    return inet_ntoa(this->connAddr.sin_addr);
}

int Socket::getPort() {
    return ntohs(this->connAddr.sin_port);
}
