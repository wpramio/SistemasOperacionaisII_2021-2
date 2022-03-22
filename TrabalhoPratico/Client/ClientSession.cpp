#include "ClientSession.hpp"


ClientSession::ClientSession(string profile, string ip, string port) {

    Client client(ip, stoi(port));

    //Inicializa sessao no servidor
    string sessionMsg = "SESSION:" + profile;

    if(client.sendMessage(sessionMsg) < 0) {
        cout << "!> ERROR - Session request" << endl;
        exit(1);
    }


    if(client.receiveMessage() < 0) {
        cout << "!> ERROR - Server response" << endl;
        exit(1);
    }

    
    //Pega o profile que iniciou a sessao
    string sessionResponse = client.getMessage().substr(client.getMessage().find("::") + 1);   

    //PNF == Profile not found
    if(sessionResponse == "PNF") {
        cout << "!> ERROR - Profile not found";
        exit(1);
    }

    //Mais condiçoes

    cout << ">>SUCCESS - Session started" << endl;
    
    //Inicia a sessao
    thread sessionThread(session, profile, &client);
    thread feedThread(feed, &client);

    //Linhas de execucao
    sessionThread.join();
    feedThread.join();

}

//Mudar esse nome
void ClientSession::session(string profile, Client *client) {

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

            //Inicializa sessao no servidor

            //comando:prefil::perfil pra seguir

            string followMsg = "FOLLOW:" + profile + "::" + content;

            if(client->sendMessage(followMsg) < 0) {
                cout << "!> ERROR - Follow request" << endl;
                continue;
            }

            if(client->receiveMessage() < 0) {
                cout << "!> SERVER ERROR - Server response" << endl;
                exit(1);
            }

            //Pega o profile que iniciou a sessao
            string followResponse = client->getMessage().substr(0, client->getMessage().find(":"));   

            //PNF == FOLLOW ERROR
            if(followResponse == "PNF") {
                cout << "!> ERROR - Profile not found" << endl;
                continue;
            }


            cout << "SUCCESS - Following " << content << endl;

        
        
        }else if (command == "SEND") {

            if(content.length() > TWEETMAX) {

                cout << "!> ERROR - Max tweet size is 280" << endl;
                continue;

            }


            //Send to server

            
        }else {

            cout << "!> ERROR - Invalid command" << endl;
            continue;

        }
    

    }

}


void ClientSession::feed(Client *client) {
    cout << "\nThread feed" << endl;

    while (true) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (client->nonBlockingReceiveMessage() < 0) {
            continue;
        }

        string message = client->getMessage();
        string commandStr = message.substr(0, message.find(","));


        cout << "MESSAGE FROM FEED - " << message << endl;
    }
//         if (commandStr != "notify") {
//             continue;
//         }
}