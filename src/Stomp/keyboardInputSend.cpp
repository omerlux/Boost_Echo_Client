//
// Created by omerlux@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "keyboardInputSend.h"

extern bool do_shutdown;

keyboardInputSend::keyboardInputSend(int id, ConnectionHandler& CH):id(id), CH(CH){}

void keyboardInputSend::run(){
    //------------------- start edit 11/1 ------------------------
    std::string input;
    while (!do_shutdown){                             // shutdown = closing the client
        getline(std::cin,input);            //reading from keyboard
        CH.stompSendProcess(input);            // the send process
        input = "";
    }
    //------------------- end edit 11/1 --------------------------
}