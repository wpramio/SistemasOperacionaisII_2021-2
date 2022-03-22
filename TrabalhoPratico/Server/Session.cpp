#include "Session.hpp"

Session::Session() {

} 

void Session::start(Server *server, string command, string content) {


        int clientUuid;

        if(server->clientAlreadyExists(content)) {
            
            
            clientUuid = server->getProfileUuid(content);
            auto client = server->getProfile(clientUuid);
            //Tenta iniciar a sessao
            //Incrementa seções ativas
            if(!client.setActiveSession()) {
                
                cout << "There are already 2 active sessions" << endl;
                server->sendMessage("There are already 2 active sessions");
                return;
            
            }

            server->startClientSession(clientUuid);
        }

        clientUuid = server->setNewClient(content);

        server->startClientSession(clientUuid);

        cout <<"CHEGOU AQUI" << endl;
        server->sendMessage("Logged in");
}