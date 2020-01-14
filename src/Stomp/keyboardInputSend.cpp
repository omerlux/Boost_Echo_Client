//
// Created by omerlux@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "../include/keyboardInputSend.h"

extern bool do_shutdown;
extern bool logout;
extern bool first_login;
extern std::string last_input;

keyboardInputSend::keyboardInputSend(int id, ConnectionHandler& CH):id(id), CH(CH){}

void keyboardInputSend::run(){
    //------------------- start edit 11/1 ------------------------
    std::string input;
    while (!do_shutdown){                          // shutdown = closing the client, only if logged out!!!!
        if(last_input=="")       //read line if we didn't save any input before
            getline(std::cin,input);            //reading from keyboard
        else {                   //we saved input - use it instead of a new one
            CH.stompSendProcess(last_input);         // the send process
            last_input="";
        }

        if((input!="") & (!logout)) {
            ///------------------logged in procces send------------
            CH.stompSendProcess(input);         // the send process
            input = "";
        }else if((input=="shutdown") & (logout)) {       //only if user logged out, we will allow shutdown
            ///------------------shutdown send---------------------
            do_shutdown = true;
        }else if((logout) & (input.find("login")!= std::string::npos)){     //user wants to log in again
            ///----------login again - rerun threads proccess------
            last_input=input;
            logout=false;       //for making the socketReader, to run on the while
            first_login =false; //for making the socketReader NOT read the socket until we are logged in again
            break;              //close the run loop - make the thread join
        }
    }
    //------------------- end edit 11/1 --------------------------
}