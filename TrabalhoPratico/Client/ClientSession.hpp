#include <iostream>
#include <string>
#define MSG_MAX_LEN 128
#include <thread>
#include "Client.hpp"
#include "CommManager.hpp"

using namespace std;

class ClientSession {


public:

    ClientSession(string profile, string ip, string port);
    
    //Static for using in threads
    static void session(string profile, string ip, int port) ;
    static void feed(string profile, string ip, int port) ;

};