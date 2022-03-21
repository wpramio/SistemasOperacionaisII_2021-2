#include <iostream>
#include <string>
#define TWEETMAX 280
#include <thread>

using namespace std;

class ClientSession {


public:

    ClientSession(string profile, string ip, string port);
    
    //Static for using in threads
    static void session(string profile) ;
    static void feed();

    

};