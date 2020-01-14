//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CONNECTIONHANDLER_H
#define BOOST_ECHO_CLIENT_CONNECTIONHANDLER_H


#include <string>
#include <iostream>
#include "User.h"
#include <boost/asio.hpp>
#include <mutex>

using boost::asio::ip::tcp;

class ConnectionHandler {
private:
    std::string host_;
    short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;
    User& user;
    bool registered;
    std::string oldUser;            //saving username to change user in cpp
    std::mutex _mutex;             //mutex for locking sendFrame


public:
    ConnectionHandler(std::string host, short port, User& user);
    virtual ~ConnectionHandler();

    // Connect to the remote machine
    bool connect(std::string host, short port);

    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);

    // Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);

    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getFrame(std::string& line);

    // Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendFrame(std::string& line);

    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string& frame, char delimiter);

    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string& frame, char delimiter);

    // Close down the connection properly.
    void close();

    //------------------- start edit 11/1 ------------------------
    // stompSendProcess - make a frame and send it to the server
    void stompSendProcess(std::string &input);
    //------------------- end edit 11/1 --------------------------

    //------------------- start edit 11/1 ------------------------
    // stompSendProcess - Receive a frame from server and act
    void stompReceivedProcess(std::string &income);
    //------------------- end edit 11/1 --------------------------

    //------------------- start edit 12/1 ------------------------
    void logoutProcess ();
    //------------------- end edit 11/1 --------------------------
}; //class ConnectionHandler


#endif //BOOST_ECHO_CLIENT_CONNECTIONHANDLER_H
