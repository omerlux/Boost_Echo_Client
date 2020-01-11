//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SOCKETREADER_H
#define BOOST_ECHO_CLIENT_SOCKETREADER_H
#include "stompConnectionHandler.h"

class socketReader {
private:
    //------------------- start edit 10/1 ------------------------
    bool &logout;
    stompConnectionHandler &CH;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    socketReader (stompConnectionHandler &CH, bool &logout);
    void run();
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_SOCKETREADER_H
