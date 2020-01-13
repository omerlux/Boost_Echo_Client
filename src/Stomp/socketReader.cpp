//
// Created by omerlux@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "socketReader.h"

extern bool logout;

socketReader::socketReader(int id, ConnectionHandler& CH):id(id),CH(CH){}

void socketReader::run(){
    //------------------- start edit 11/1 ------------------------
    std::string income;
    while (!logout){
        if(income!="") {
            CH.getFrame(income);                              //returns a FRAME of string - Decoder
            CH.stompReceivedProcess(income);                  // the receiving process    - Process
            income = "";
        }
    }
    //------------------- end edit 11/1 --------------------------
}