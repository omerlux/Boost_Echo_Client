//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "stompClient.h"
#include <stdlib.h>
#include "User.h"
#include "ConnectionHandler.h"
#include "socketReader.h"
#include "keyboardInputSend.h"
#include <mutex>
#include <thread>

bool do_shutdown;

int main (int argc, char *argv[]) {

    User* user = new User();
    ConnectionHandler connectionHandler ("0",0,user);
    socketReader socketReader_task (1,connectionHandler);
    keyboardInputSend keyboardIS_task(2,connectionHandler);

    while(!do_shutdown){        // will shutdown when got a specific string after logged out
        std::thread keyboardIS_thread (&keyboardInputSend::run, &keyboardIS_task);
        std::thread socketReader_thread (&socketReader::run, &socketReader_task);

        socketReader_thread.join();
        keyboardIS_thread.join();
    }

    delete user;
    return 0;
}
