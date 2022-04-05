#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <time.h>
#include <chrono>
#include <queue>
#include "../shared/Logger.hpp"

#include "Notification.hpp"
#include "Profile.hpp"

using namespace std;

class NotificationsManager {

private:


public:

    void registerReceivedNotification(Profile* profile, string message);
    void pushNotificationToFollowers(Profile* profile, Notification* notification);
    string getDateTime();

};
