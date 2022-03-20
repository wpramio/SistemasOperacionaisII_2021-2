#include "Client.hpp"


//Constructor
Client::Client(string ip, int port) {

    /*IPv4, type(UDP), protocol
    Creates an endpoint for communication and returns a file
    descriptor that refers to that endpoint
    */
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketfd < 0) {

        cout << "ERROR - Could not create socket";
        exit(1);

    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    this->serverAddr.sin_port = htons(port); //big endian



    int connectfd = connect(this->socketfd, (struct sockaddr *)&this->serverAddr, sizeof(serverAddr));

    if(connectfd < 0) {

        cout << "ERROR - Could not connect";
        exit(1);

    }

    cout << "SUCCESS - Connecet to " << ip << "on port: " << port << endl;


}