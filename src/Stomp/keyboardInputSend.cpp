//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "keyboardInputSend.h"
#include "connectionHandler.h"

keyboardInputSend::keyboardInputSend(ConnectionHandler &connectionHandler, bool &logout):
                    connectionHandler(connectionHandler),logout(logout) {}

void keyboardInputSend:: run(){
    //------------------- start edit 10/1 ------------------------
    std::string input;
    while (!logout){
        getline(std::cin,input);
        if (input.compare("logout"))
            logout=true;
        if()
        connectionHandler.sendLine(input);
    }
    //------------------- end edit 10/1 --------------------------
}