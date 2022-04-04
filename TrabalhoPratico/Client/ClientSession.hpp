#include <iostream>
#include <string>
#define MSG_MAX_LEN 128
#include <thread>
#include "Client.hpp"
#include "CommManager.hpp"

using namespace std;

class ClientSession {

private:

    CommManager* commManager;
    string profile;

public:

    ClientSession(string profile, string ip, string port);
    void startThreads();
    
    //Static for using in threads
    static void getUserInput(ClientSession* clientSession);
    static void getServerResponses(ClientSession* clientSession) ;

};