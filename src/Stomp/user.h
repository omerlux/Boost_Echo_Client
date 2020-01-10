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

class user {
private:
    //------------------- start edit 10/1 ------------------------
    vector <Book> inventory;
    unordered_map <int, string> idByUser_topic_map;
    unordered_map <int, bool> receiptId_returned_map;
    int topicIdCounter;
    int receiptIdCounter;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    //Constructor
    user();

    //Getters
    unordered_map<int,string> get_idByUser_topic_map ();
    unordered_map<int,bool> get_receiptId_returned_map();
    vector <Book> getInventory();

    //adders
    void addBook(Book book);
    void subTopic(string topic);
    void returnedReceiptId(int receiptId);
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_USER_H
