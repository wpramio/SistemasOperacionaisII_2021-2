#include "Client.hpp"

#define MAXLINE 1024
//Constructor
Client::Client(string ip, int port) {

    /*IPv4, type(UDP), protocol
    Creates an endpoint for communication and returns a file
    descriptor that refers to that endpoint
    */
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    char buffer[MAXLINE];
    string hello = "Hello from client";


    if(socketfd < 0) {

        cout << "!> ERROR - Could not create socket";
        exit(1);

    }

    cout << ">> SUCCESS - Socket client created" << endl;

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    this->serverAddr.sin_port = htons(port); //big endian

    int  n;
    socklen_t len;

    len = sizeof(this->serverAddr); // len is value/resuslt

    sendto(socketfd, (const char *)hello.c_str(), hello.length(),
        MSG_CONFIRM, (const struct sockaddr *)&this->serverAddr,
        len);

    n = recvfrom(socketfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &this->serverAddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);


}