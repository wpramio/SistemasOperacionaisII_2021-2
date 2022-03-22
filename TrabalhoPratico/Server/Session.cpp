#include "Session.hpp"

Session::Session() {

} 

void Session::start(Server *server, string command, string content) {


        int clientUuid;

        //Procura o perfil na estrutura de dados de clientes no servidor
        if(server->clientAlreadyExists(content)) {
            
            clientUuid = server->getProfileUuid(content);
            auto client = server->getProfile(clientUuid);
            //Tenta iniciar a sessao
            //Incrementa seções ativas
            if(!client.setActiveSession()) {
                
                cout << "There are already 2 active sessions" << endl;
                //Avisa que não é possivel iniciar uma nova sessao
                server->sendMessage("There are already 2 active sessions");
                return;
            
            }

            //Inicia uma nova sessao
            server->startClientSession(clientUuid);
        
        }else {

            clientUuid = server->setNewClient(content);

            server->startClientSession(clientUuid);

            cout <<"CHEGOU AQUI" << endl;
            server->sendMessage("Logged in");
        }
}