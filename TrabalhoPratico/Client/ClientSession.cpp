#include "ClientSession.hpp"

ClientSession::ClientSession(string profile, string ip, string port) {

    thread sessionThread(session, profile);
    thread feedThread(feed);


    //Linhas de execucao
    sessionThread.join();
    feedThread.join();

}


void ClientSession::session(string profile) {

    cout << "Thread session" << endl;

    string message;

    while(true) {

        cout << "-> ";
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

            if(content.length() > TWEETMAX) {

                cout << "!> ERROR - Max tweet size is 280" << endl;
                continue;

            }


            //Send to server

            
        }
    

    }

}


void ClientSession::feed() {
    cout << "\nThread feed" << endl;
}