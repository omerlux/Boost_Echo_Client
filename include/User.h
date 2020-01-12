//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <vector>
#include <include/Book.h>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class User {
private:
    //------------------- start edit 10/1 ------------------------
    std::string name;
    vector <Book*> inventory;
    unordered_map <string, int> topic_idByClient_map;
    unordered_map <int, string> receiptId_returned_map;
    int topicIdCounter;
    int receiptIdCounter;
    unordered_map <string,string>  askedBook_topic_map;
    //------------------- end edit 10/1 --------------------------

public:
    //------------------- start edit 10/1 ------------------------
    //Constructor
    User();
    //Destructor
    ~User();

    //Getters
    unordered_map<string,int> &get_topic_idByClient_map ();
    unordered_map<int,string> &get_receiptId_returned_map();
    unordered_map<string,string> &get_askedBook_topic_map();
    vector <Book*> &getInventory();
    std::string getName();

    //SetName
    void setName(std::string name);

    //adders
    void addBook(Book *book);
    void addAskedBook (string bookname, string topic);

    //askedBook functions
    void removeAskedBook(string bookname);
    bool wasAskedForBook(string bookname);

    //topic
    int subTopic(string &topic);        //works as a getter for a topic as well!!
    int unsubtopic(string topic);


    //receipt
    int addReceiptId(string details);
    void returnedReceiptId(int receiptId);
    string receiptStatus (int receiptId);
    //------------------- end edit 10/1 --------------------------
};


#endif //BOOST_ECHO_CLIENT_USER_H
