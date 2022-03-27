#pragma once

#include <iostream>
#include <string>

using namespace std;

class Notification {

private:

    int uuid;
    int timestamp;
    int pending;
    string message;


public:

    Notification(int uuid, int timestamp, string message);
    int getUuid();
    int getTimestamp();
    string getMessage();
    int getPending();
    void incrementPending();
    void decrementPending();

};