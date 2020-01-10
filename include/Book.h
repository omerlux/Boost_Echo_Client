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
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    //Constructor
    Book(string bookname, string topic, string loner);

    //Getters
    string getBookname();
    string getTopic();
    string getLoner();

    //Setter
    void setLoner(string loner);
    //------------------- end edit 10/1 --------------------------

};


#endif //BOOST_ECHO_CLIENT_BOOK_H
