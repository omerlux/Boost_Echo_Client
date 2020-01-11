//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "Book.h"
//------------------- start edit 10/1 ------------------------
Book::Book(string bookname, string topic, string loner):
                    bookname(bookname), topic(topic), loner(loner){}

Book::~Book(){};

void Book::setLoner(string &loner) { this->loner=loner;}

string Book::getBookname() {return this->bookname;}

string Book::getTopic() {return this->topic;}

string Book::getLoner() {return this->loner;}
//------------------- end edit 10/1 --------------------------
