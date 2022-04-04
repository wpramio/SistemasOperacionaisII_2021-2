#include "Session.hpp"

Session::Session(int port, Profile* prof) {
  
  this->commManager = new CommManager(port);
  this->notificationsManager = new NotificationsManager();
  this->profile = prof;

}

void Session::messagesListener(Session* session, Server* server) {

    // pode quebrar, talvez usar os proprios atributos diretamente
    auto profile = session->profile;
    auto commManager = session->commManager;
    auto notificationsManager = session->notificationsManager;
    
    string username = profile->getUserName();
    cout << ">> New session thread created for " << username;
    cout << ", listening on port " << server->getNewSessionPort() << endl;

    while(true) {

        string message = commManager->receiveMessage();
        //Pega o comando
        string command = message.substr(0, message.find(":"));
        //Pega o username
        string content = message.substr(message.find(":") + 1);

        if (command == "FOLLOW") {

            // TODO: agrupar num Gerenciador de Perfis

            string toFollow = content.substr(content.find("::") + 2);

            // Recupera o perfil
            Profile *toFollowProf = server->getProfileByName(toFollow);

            LOG(DEBUG) << username << " quer SEGUIR " << toFollow;

            if (!server->clientAlreadyExists(toFollow)) {

                // perfil nao encontrado
                commManager->sendMessage("Profile Not Found");

            // Testa se ja esta seguindo
            } else if (toFollowProf->isFollowedBy(profile)) {

                commManager->sendMessage("You already follow this profile");

            } else {

                //Adiciona na lista de Seguidores do alvo
                toFollowProf->pushToFollowers(profile);

                commManager->sendMessage("You are now following " + toFollow);

            }

        } else if (command == "SEND") {

            string tweet = content.substr(content.find("::") + 2);

            //Constroi notificacao e guarda no server
            notificationsManager->registerReceivedNotification(profile, tweet);
            commManager->sendMessage("Tweet posted");

        } else if (command == "EXIT") {

            cout << "Ending session for " << username << endl;

            profile->decreaseActiveSessions();

        } else {

            cout << "Error - Invalid command" << endl;
            commManager->sendMessage("Invalid command");
            continue;

        }
    }

}

// Monitora fila toBeSent para enviar novas Notifications para o profile
void Session::notificationsToSendWatcher(Session* session) {
    
    // pode quebrar, talvez usar os proprios atributos diretamente
    auto profile = session->profile;
    
    LOG(DEBUG) << "Thread de monitoramento do toBeSent criada para " << profile->getUserName();

    while(true) {
        
        if (profile->getToBeSentSize() > 0) {

            LOG(DEBUG) << "Notification detectada";

            Notification* notif = profile->popToBeSent();
            session->commManager->sendMessage("notify::" + notif->print());

        };

    }

}