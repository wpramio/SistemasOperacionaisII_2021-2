#include "Follow.hpp"

Follow::Follow() {}

void Follow::start(Server *server, string myUser, string toFollow) {

    if(!server->clientAlreadyExists(toFollow)) {

        //perfil nao encontrado
        server->sendMessage("PNF");
        return;
    }



}