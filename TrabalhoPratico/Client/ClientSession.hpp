#include <iostream>
#include <string>
#define TWEETMAX 280
#include <thread>
#include "Client.hpp"

using namespace std;

class ClientSession {


public:

    ClientSession(string profile, string ip, string port);
    
    //Static for using in threads
    static void session(string profile, Client *client) ;
    static void feed();

    

};