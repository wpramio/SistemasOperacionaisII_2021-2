#include <string>
#define TWEETMAX 280
#include <thread>

using namespace std;

class ClientSession {

private:

    string profile;
    string ip;
    string port;

public:

    ClientSession(string profile, string ip, string port);
    void session();
    

};