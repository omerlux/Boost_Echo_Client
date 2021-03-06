//
// Created by omerlux@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "../include/socketReader.h"

extern bool logout;
extern bool first_login;

socketReader::socketReader(int id, ConnectionHandler& CH):id(id),CH(CH){}

void socketReader::run(){
    //------------------- start edit 11/1 ------------------------
    std::string income;
    while (!logout){
        //returns a FRAME of string - Decoder
        if (first_login && CH.getFrame(income)) {
            CH.stompReceivedProcess(income);                  // the receiving process    - Process
            income = "";
        }
    }
    //------------------- end edit 11/1 --------------------------
}