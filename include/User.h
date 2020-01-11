//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <vector>
#include <include/Book.h>
#include <bits/unordered_map.h>

using std::vector;
using std::unordered_map;

class User {
private:
    //------------------- start edit 10/1 ------------------------
    vector <Book*> inventory;
    unordered_map <string, int> topic_idByClient_map;
    unordered_map <int, bool> receiptId_returned_map;
    int topicIdCounter;
    int receiptIdCounter;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    //Constructor
    User();
    //Destructor
    ~User();

    //Getters
    unordered_map<string,int> &get_topic_idByClient_map ();
    unordered_map<int,bool> &get_receiptId_returned_map();
    vector <Book*> &getInventory();

    //adders
    void addBook(Book *book);

    //topic
    int subTopic(string &topic);        //works as a getter for a topic as well!!
    int unsubtopic(string topic);


    //receipt
    int addReceiptId();
    void returnedReceiptId(int receiptId);
    bool receiptStatus (int receiptId);
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_USER_H
