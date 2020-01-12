//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "socketReader.h"
#include "stompConnectionHandler.h"

extern bool logout;


socketReader::socketReader(stompConnectionHandler &CH,string &str):CH(CH){}

void socketReader:: run(){
    //------------------- start edit 11/1 ------------------------
    std::string income;
    while (!logout){
        CH.getFrame(income);                              //returns a FRAME of string - Decoder
        CH.stompReceivedProcess(income);                  // the receiving process    - Process
        income ="";
    }
    //------------------- end edit 11/1 --------------------------
}

