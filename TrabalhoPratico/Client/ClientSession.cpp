#include "ClientSession.hpp"

ClientSession::ClientSession(string profile, string ip, string port) {

    this->profile = profile;
    this->ip = ip;
    this->port = port;

}

 {

void ClientSession::session() {

    string message;

    while(true) {


        //Das threads
        //Uma recebe os novos tweets e outra envia

        cout << "Tweet: ";
        getline(cin, message); 

        //Pega o comando
        string command = message.substr(0, message.find(" "));
        //Pega a instrução do comando
        string content = message.substr(message.find(" ") + 1, message.length());


        if(command == "FOLLOW") {
        
            if(content.at(0) != '@') {

                cout <<"!> ERROR - Profile must start with '@'" << endl;
                continue;

            }

            if(content == profile) {

                cout << "!> ERROR - You can't follow yourself" << endl;
                continue;

            }

            //Send to server

        
        
        }else if (command == "SEND")
        {

            if(content > TWEETMAX) {

                cout << "!> ERROR - Max tweet size is 280" << endl;
                continue;

            }


            //Send to server

            
        }
    

    }

}