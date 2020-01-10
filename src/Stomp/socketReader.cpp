//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "socketReader.h"
#include "connectionHandler.h"

socketReader::socketReader(ConnectionHandler &connectionHandler, bool &logout):
                connectionHandler(connectionHandler),logout(logout){}

void socketReader:: run(){
    //------------------- start edit 10/1 ------------------------
    std::string income;
    while (!logout){
        getline(std::cin,input);
        if (input.compare("logout"))
            logout=true;
        connectionHandler.getLine(input);       /// THIS IS NOT A LINE, ITS A MESSAGE
    }
    //------------------- end edit 10/1 --------------------------
}