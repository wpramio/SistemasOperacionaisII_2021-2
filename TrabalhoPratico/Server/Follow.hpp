#pragma once

#include "Server.hpp"
#include "Follow.hpp"

class Follow {


public:
    Follow();
    void start(Server *server, string myUser, string toFollow); 

};