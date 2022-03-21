#include "Server.hpp"

int main() {


    Server server;

    while(true) {

        string message = server.receiveMessage();
        cout << message << endl;


        string command = message.substr(0, message.find(":"));
        cout << command << endl;
        string content;
        cout << content << endl;

        if(command == "SESSION") {


            cout << "CHEGOU";
            //Pega o username
            content = message.substr(message.find(":") + 1);

            if(server.clientAlreadyExists(content)) {
                cout << "Já existe" << endl;
                //Incrementa seções ativas
            }

            server.setNewClient(content);


            server.sendMessage("SUCESS");


        }else if(command == "FOLLOW") {



        }else if(command == "SEND") {

        }


    }
    

    return 0;
}