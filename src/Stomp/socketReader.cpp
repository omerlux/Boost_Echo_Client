//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "socketReader.h"
#include "stompConnectionHandler.h"

socketReader::socketReader(stompConnectionHandler &CH, bool &logout):
        CH(CH),logout(logout){}

void socketReader:: run(){
    //------------------- start edit 11/1 ------------------------
    std::string income;
    while (!logout){
        CH.getFrame(income);                              //returns a FRAME of string
        if(income.find("ERROR")!=std::string::npos) {     //FORUM: close the connection
            logout=true;
        }
        ///CH.stompReceiveProcces.process(income)

    }
    //------------------- end edit 11/1 --------------------------
}