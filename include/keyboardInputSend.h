//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#define BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#include "stompConnectionHandler.h"

class keyboardInputSend {
private:
    //------------------- start edit 10/1 ------------------------
    bool shutdown;
    //stompConnectionHandler &CH;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 12/1 ------------------------
    keyboardInputSend ();
    void setShutdown(bool state);
    bool getShutdown();
    void run();
    //------------------- end edit 12/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
