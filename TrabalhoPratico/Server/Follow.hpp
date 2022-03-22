#pragma once

#include "Server.hpp"

class Follow {


public:
    Follow();
    void start(Server *server, string myUser, string toFollow);


};