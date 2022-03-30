#include "Follow.hpp"

Follow::Follow() {}

void Follow::start(Server *server, string myUser, string toFollow) {

    if(!server->clientAlreadyExists(toFollow)) {

        //perfil nao encontrado
        server->sendMessage("Profile Not Found");
        return;
    }
    //Da pra otimizar
    int myUserUuid = server->getProfileUuid(myUser);
    int toFollowUuid = server->getProfileUuid(toFollow);

    //Recupera os perfis
    Profile *myUserProf = server->getProfile(myUserUuid);
    Profile *toFollowProf = server->getProfile(toFollowUuid);

    // Testa se ja esta seguindo
    if (myUserProf->isFollowing(toFollowProf)) {

        server->sendMessage("You already follows this profile");
        return;

    }

    //Adiciona na lista de Seguindo
    myUserProf->setFollowing(toFollowProf);

    //Adiciona na lista de Seguidores do alvo
    toFollowProf->setFollowers(myUserProf);

    server->sendMessage("You are now following " + toFollow);

}
