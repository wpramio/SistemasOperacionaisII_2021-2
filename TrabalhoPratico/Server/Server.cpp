#include "Server.hpp"

Server::Server()
{

    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    char buffer[MAXLINE];
    string hello = "Hello from server";

    if (socketfd < 0)
    {

        cout << " !> ERROR - Could not create socket";
        exit(1);
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(PORT);              // big endian
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // big endian

    bzero(&(serverAddr.sin_zero), 8);

    cout << ">> SUCCESS - Socket created" << endl;

    // Bind - unique local name to the socket with descriptor socket
    if (bind(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {

        cout << "!> ERROR - Binding error";
        exit(1);
    }

    cout << ">> SUCCESS - Server is up on "
         << " PORT: " << PORT << endl;
    cout << ">> STATUS - Awaiting for clients..." << endl;

    int  n;
    socklen_t len;

    len = sizeof(this->clientAddr); // len is value/resuslt

    n = recvfrom(socketfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&this->clientAddr,
                 &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(socketfd, (const char *)hello.c_str(), hello.length(),
           MSG_CONFIRM, (const struct sockaddr *)&this->clientAddr,
           len);
    printf("Hello message sent.\n");
}