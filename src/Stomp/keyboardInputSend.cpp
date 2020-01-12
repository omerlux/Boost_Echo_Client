//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "keyboardInputSend.h"
#include "stompConnectionHandler.h"

keyboardInputSend::keyboardInputSend(stompConnectionHandler &CH):
                    CH(CH),shutdown(false) {}

void keyboardInputSend:: run(){
    //------------------- start edit 11/1 ------------------------
    std::string input;
    while (!shutdown){                             // shutdown = closing the client
        getline(std::cin,input);            //reading from keyboard
        CH.stompSendProcess(input);            // the send process
        input = "";
    }
    //------------------- end edit 11/1 --------------------------
}

/**
 * This function is to change the state of the thread
 * @param state
 */
void keyboardInputSend::setShutdown(bool state) {
    //------------------- start edit 12/1 ------------------------
    this->shutdown=state;
    //------------------- end edit 12/1 --------------------------
}