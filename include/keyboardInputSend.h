//
// Created by omerlux@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
#define BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H


#include "ConnectionHandler.h"

class keyboardInputSend {
public:
    keyboardInputSend(int id, ConnectionHandler& connectionHandler);
    void run();
private:
    const int id;
    ConnectionHandler &CH;
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDINPUTSEND_H
