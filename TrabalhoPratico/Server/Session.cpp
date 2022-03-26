#include "Session.hpp"

Session::Session() {

} 

void Session::start(Server *server, string command, string content) {


        int clientUuid;

        //Procura o perfil na estrutura de dados de clientes no servidor
        if(server->clientAlreadyExists(content)) {
            
            clientUuid = server->getProfileUuid(content);
            auto client = server->getProfile(clientUuid);

            // Checa se pode criar uma nova sessao
            if(client->getActiveSessions() >= 2 ) {
                
                cout << "Session creation error: There are already 2 active sessions for " + client->getUserName() << endl;
                //Avisa que não é possivel iniciar uma nova sessao
                server->sendMessage("There are already 2 active sessions");
                return;
            
            }
        
        } else {
            
            // ainda nao esta presente, insere um novo cliente
            clientUuid = server->setNewClient(content);

        }

        server->registerNewClientSession(clientUuid);
        server->sendMessage("Logged in");
}