#include "ClientSession.hpp"


ClientSession::ClientSession(string profile, string ip, string port) {

    CommManager commManager(ip, stoi(port));

    //Inicializa sessao no servidor
    string sessionMsg = "SESSION:" + profile;

    if(commManager.sendMessage(sessionMsg) < 0) {
        cerr << "!> ERROR - Session request not sent" << endl;
        exit(1);
    }


    if(commManager.receiveMessage() < 0) {
        cerr << "!> ERROR - Server response not received" << endl;
        exit(1);
    }

    
    //Pega o profile que iniciou a sessao
    string sessionResponse = commManager.getMessage();   

    cout << endl << "Server response: " << sessionResponse << endl;

    if(sessionResponse == "There are already 2 active sessions") {
        cerr << "!> ERROR - Too many sessions at the same time" << endl;
        exit(1);
    }

    //Mais condiçoes

    cout << ">> SUCCESS - Session started" << endl;
    
    //Inicia a sessao
    thread sessionThread(session, profile, &commManager);
    thread feedThread(feed, &commManager);

    //Linhas de execucao
    sessionThread.join();
    feedThread.join();

}

//Mudar esse nome
void ClientSession::session(string profile, CommManager *commManager) {

    cout << "Thread session" << endl;

    string message;

    while(true) {

        cout << "-> ";
        getline(cin, message); 

        //Pega o comando
        string command = message.substr(0, message.find(" "));
        //Pega o conteudo do comando
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

            string followMsg = "FOLLOW:" + profile + "::" + content;

            if(commManager->sendMessage(followMsg) < 0) {
                cout << "!> ERROR - Follow request" << endl;
                continue;
            }

            if(commManager->receiveMessage() < 0) {
                cout << "!> SERVER ERROR - Server response" << endl;
                exit(1);
            }

            //Pega o profile que iniciou a sessao
            string followResponse = commManager->getMessage();   

            //PNF == FOLLOW ERROR
            if(followResponse == "Profile Not Found") {
                cout << "!> ERROR - Profile not found" << endl;
                continue;
            }


            if(followResponse == "You already follows this profile") {
                cout << "!> ERROR - You already follows this profile" << endl;
                continue;
            }


            cout << "SUCCESS - " << followResponse << endl;

        
        
        }else if (command == "SEND") {

            if(content.length() > MSG_MAX_LEN) {

                cout << "!> ERROR - Message max size is " << std::to_string(MSG_MAX_LEN) << endl;
                continue;

            }

            string tweet = "SEND:" + profile + "::" + content;

            //Send to server
            if(commManager->sendMessage(tweet) < 0) {
                cout << "!> ERROR - Send Tweet " << endl;
                continue;
            }

            if(commManager->receiveMessage() < 0) {
                cout << "!> SERVER ERROR - Server response" << endl;
                exit(1);
            }

            cout << "!> SUCCESS - " << commManager->getMessage() << endl;


        }else if(command == "EXIT"){

            commManager->sendMessage("EXIT:" + profile);

            cout << "!> Leaving..." << endl;

            exit(0);

        }else {

            cout << "!> ERROR - Invalid command" << endl;
            continue;

        }
    

    }

}


void ClientSession::feed(CommManager *commManager) {
    cout << "\nThread feed" << endl;

    while (true) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (commManager->nonBlockingReceiveMessage() < 0) {
            continue;
        }

        string message = commManager->getMessage();
        string commandStr = message.substr(0, message.find(","));


        if(message != "Profile Not Found") {
            continue;
        }

        cout << "MESSAGE FROM FEED - " << message << endl;
    }
//         if (commandStr != "notify") {
//             continue;
//         }
}