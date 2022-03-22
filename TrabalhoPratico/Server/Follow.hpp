#pragma once

#include "Server.hpp"
#include "Follow.hpp"
#include "Socket.hpp"

class Follow {


public:
    Follow();
    void start(Server *server, string myUser, string toFollow, Socket sock); 

};