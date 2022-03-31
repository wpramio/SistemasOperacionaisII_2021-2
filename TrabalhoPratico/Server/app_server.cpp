#include "Server.hpp"

structlog LOGCFG = {};

int main() {


    Server server;

    while(true) {

        string message = server.receiveMessage();
        //Pega o comando
        string command = message.substr(0, message.find(":"));
        //Pega o username
        string username = message.substr(message.find(":") + 1);

        if(command == "SESSION") {

            if (server.canStartSession(username)) {
                server.incrementNewSessionPort();
                string newPort = to_string(server.getNewSessionPort());
                server.sendMessage("Logged in, new port is::" + newPort);

                server.startSession(username);
            }

        }

    }
    
    return 0;
}