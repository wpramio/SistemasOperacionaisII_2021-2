#include "Follow.hpp"

Follow::Follow() {}

void Follow::start(Server *server, string myUser, string toFollow, Socket sock) {

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

    //Adiciona em seguindo
    myUserProf->setFollowing(toFollowProf, sock);

    //Adiciona em seguidor
    toFollowProf->setFollowers(myUserProf);


}
