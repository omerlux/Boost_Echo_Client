//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "keyboardInputSend.h"
#include "stompConnectionHandler.h"

keyboardInputSend::keyboardInputSend(stompConnectionHandler &CH, bool &logout):
                    CH(CH),logout(logout) {}

void keyboardInputSend:: run(){
    //------------------- start edit 11/1 ------------------------
    std::string input;
    while (!logout){
        getline(std::cin,input);            //reading from keyboard
        CH.stompSendProcess(input);
        input = "";
     /*   if (input.compare("logout"))
            logout=true;            ///to stop writing


        //CH.sendLine(input);     //need to convert input to a FRAME */
    }
    //------------------- end edit 11/1 --------------------------
}