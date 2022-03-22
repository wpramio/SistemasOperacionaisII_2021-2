#include "Server.hpp"
#include "Socket.hpp"
#include "Session.hpp"
#include "Follow.hpp"


int main() {


    Server server;

    while(true) {

        string message = server.receiveMessage();
        //Pega o socket que enviou a mensagem
        Socket sock = server.getConnection();
        //Pega o comando
        string command = message.substr(0, message.find(":"));
        //Pega o username
        string content = message.substr(message.find(":") + 1);
         
        int clientUuid;

        if(command == "SESSION") {

            Session session;
            session.start(&server, command, content);

            continue;


        }else if(command == "FOLLOW") {

            Follow follow;
            string myUser = content.substr(0, content.find("::"));
            string toFollow = content.substr(content.find("::") + 2);

            cout << "SEGUIR " << myUser << " " << toFollow << endl;
            
            follow.start(&server, myUser, toFollow, sock);


        }else if(command == "SEND") {

        }


    }
    

    return 0;
}