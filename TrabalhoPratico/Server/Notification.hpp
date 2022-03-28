#pragma once

#include <iostream>
#include <string>

using namespace std;

class Notification {

private:

    string user;
    string timestamp;
    int pending;
    string message;


public:

    Notification(string user, int timestamp, string message);
    string getUser();
    string getTimestamp();
    string getMessage();
    int getPending();
    void incrementPending();
    void decrementPending();

};