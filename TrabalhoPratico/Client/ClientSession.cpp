#include "ClientSession.hpp"


ClientSession::ClientSession(string profile, string ip, string port) {

    CommManager commManager(ip, stoi(port));
    this->profile = profile;

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

    string newPort = sessionResponse.substr(sessionResponse.find("::") + 2);
    this->commManager = new CommManager(ip, stoi(newPort));

    //Mais condiçoes

    cout << ">> SUCCESS - Session started" << endl;
    
}

void ClientSession::startThreads() {

    thread userInputThread(getUserInput, this);
    thread serverResponsesThread(getServerResponses, this);

    userInputThread.join();
    serverResponsesThread.join();

}

void ClientSession::getUserInput(ClientSession* clientSession) {

    auto commManager = clientSession->commManager;
    string profile = clientSession->profile;

    cout << "getUserInput Thread" << endl;

    string message;

    while(true) {

        cout << "Enter your command:" << endl;
        cout << "-> ";
        getline(cin, message); 

        //Pega o comando
        string command = message.substr(0, message.find(" "));
        //Pega o conteudo do comando
        string content = message.substr(message.find(" ") + 1, message.length());


        if (command == "FOLLOW") {
        
            if (content.at(0) != '@') {

                cout <<"!> ERROR - Profile must start with '@'" << endl;
                continue;

            }

            if (content == profile) {

                cout << "!> ERROR - You can't follow yourself" << endl;
                continue;

            }

            string followMsg = "FOLLOW:" + profile + "::" + content;

            if (commManager->sendMessage(followMsg) < 0) {
                cout << "!> ERROR - Follow request" << endl;
                continue;
            }
        
        } else if (command == "SEND") {

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

        } else if (command == "EXIT") {

            commManager->sendMessage("EXIT:" + profile);

            cout << "!> Leaving..." << endl;

            exit(0);

        } else {

            cout << "!> ERROR - Invalid command" << endl;
            continue;

        }
    
    }

}

void ClientSession::getServerResponses(ClientSession* clientSession) {

    auto commManager = clientSession->commManager;
    string profile = clientSession->profile;

    cout << "getServerResponses Thread" << endl;

    while(true) {

        if (commManager->receiveMessage() < 0) {
            cout << "!> SERVER ERROR - Server response" << endl;
            exit(1);
        }

        // Pega a mensagem enviada pelo server
        string response = commManager->getMessage();   

        // PNF == FOLLOW ERROR
        if (response == "Profile Not Found") {
            cout << "!> ERROR - Profile not found" << endl;
            continue;
        }

        if (response == "You already follow this profile") {
            cout << "!> ERROR - You already follow this profile" << endl;
            continue;
        }

        cout << "SUCCESS - " << response << endl;

    }

}