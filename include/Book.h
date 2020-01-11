//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>
using std::string;

class Book {
private:
    //------------------- start edit 10/1 ------------------------
    string bookname;
    string topic;
    string loner;
    bool inMyInventory;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    //Constructor
    Book(string bookname, string topic, string loner);
    //Destructor
    ~Book();

    //Getters
    string getBookname();
    string getTopic();
    string getLoner();
    bool getInMyInventory();

    //Setter
    void setLoner(string &loner);
    void setInMyInventory(bool state);
    //------------------- end edit 10/1 --------------------------

};


#endif //BOOST_ECHO_CLIENT_BOOK_H
