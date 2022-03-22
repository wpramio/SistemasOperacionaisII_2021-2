#pragma once

#include "Server.hpp"

class Session {



public:     

    Session();
    void start(Server *server, string command, string content);

};