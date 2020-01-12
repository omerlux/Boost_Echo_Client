//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "stompClient.h"
#include <stdlib.h>
#include "User.h"
#include "stompConnectionHandler.h"
#include "socketReader.h"
#include "keyboardInputSend.h"
#include <mutex>
#include <thread>

bool do_shutdown;
User* user;
stompConnectionHandler *CH;

int main (int argc, char *argv[]) {

    user = new User();
    CH = new stompConnectionHandler("0",0,user);
    socketReader socketReader_task(1);
    keyboardInputSend keyboardIS_task(2);

    while(!do_shutdown){        // will shutdown when got a specific string after logged out
        std::thread keyboardIS_thread (&keyboardInputSend::run, &keyboardIS_task);
        std::thread socketReader_thread (&socketReader::run, &socketReader_task);

        socketReader_thread.join();
        keyboardIS_thread.join();
    }
    return 0;
}
