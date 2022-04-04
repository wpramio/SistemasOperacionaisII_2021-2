#pragma once

#include <iostream>
#include <string>

#include "Profile.hpp"
#include "CommManager.hpp"
#include "NotificationsManager.hpp"
#include "Server.hpp"

using namespace std;

class Session {

private:

    CommManager* commManager;
    NotificationsManager* notificationsManager;
    Profile* profile;


public:

    Session(int port, Profile* prof);

    // threads
    static void messagesListener(Session* session, Server* server);
    static void notificationsToSendWatcher(Session* session);

};