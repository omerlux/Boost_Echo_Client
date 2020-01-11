//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#define BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#include "stompConnectionHandler.h"

class keyboardInputSend {
private:
    //------------------- start edit 10/1 ------------------------
    bool &logout;
    stompConnectionHandler &CH;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    keyboardInputSend (stompConnectionHandler &CH, bool &logout);
    void run();
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
