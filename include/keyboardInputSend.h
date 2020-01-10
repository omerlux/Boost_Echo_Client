//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#define BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#include "connectionHandler.h"

class keyboardInputSend {
private:
    //------------------- start edit 10/1 ------------------------
    bool &logout;
    ConnectionHandler &connectionHandler;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    keyboardInputSend (ConnectionHandler &connectionHandler, bool &logout);
    void run();
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
