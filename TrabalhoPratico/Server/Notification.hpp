#pragma once

#include <iostream>
#include <string>

using namespace std;

class Notification {

private:

    string username;
    string timestamp;
    int pending;
    string message;


public:

    Notification(string username, string timestamp, string message);
    string getUsername();
    string getTimestamp();
    string getMessage();
    int getPending();
    void incrementPending();
    void decrementPending();
    void setPending(int pend);
    string print();

};