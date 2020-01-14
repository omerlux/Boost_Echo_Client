//
// Created by omerlux@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "ConnectionHandler.h"
#include <string>
#include <boost/lexical_cast.hpp>// for lexical_cast()
#include <mutex>

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

extern bool logout;
bool first_login = false;
extern bool do_shutdown;

ConnectionHandler::ConnectionHandler(string host, short port, User* user):
host_(host), port_(port), io_service_(), socket_(io_service_), user(user){
    registered=false;
    oldUser="";
}

ConnectionHandler::~ConnectionHandler() {
    close();
}

bool ConnectionHandler::connect(std::string host, short port) {
    //------------------- start edit 11/1 ------------------------
    this->host_ =host;
    this->port_ =port;
    //------------------- end edit 11/1 --------------------------

    std::cout << "Starting connect to "
              << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
            tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "receive failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getFrame(std::string& line) {      //get bytes Frame (from server) -> translate to string Frame
    return getFrameAscii(line, '\0');
}

bool ConnectionHandler::sendFrame(std::string& line) {     //get string Frame -> translate to bytes Frame (to server)
    std::lock_guard<std::mutex> lock(_mutex);           //locking mutex for send frame
    return sendFrameAscii(line, '\0');
}//destructor of the mutex


bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
        do{
            if(!getBytes(&ch, 1))
            {
                return false;
            }
            if(ch!='\0')
                frame.append(1, ch);
        }while (delimiter != ch);
    } catch (std::exception& e) {
        std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}


bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
    bool result=sendBytes(frame.c_str(),frame.length());
    if(!result) return false;
    return sendBytes(&delimiter,1);
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

// stompSendProcess
void ConnectionHandler::stompSendProcess(std::string &input) {
    //------------------- start edit 14/1 ------------------------
    std::vector<string> inputBySpace;
    std::string delimiter = " ";

    //Parsing the string
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        inputBySpace.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    inputBySpace.push_back(input);
    std::string first_word = inputBySpace[0];

    ///------------------------Login send----------------------------------------------------
    if(first_word == "login"){
        size_t pos = inputBySpace[1].find(":");
        std::string host = inputBySpace[1].substr(0,pos);
        std::string port_str = inputBySpace[1].substr(pos+1);
        short port = std::stoul (port_str,nullptr,0);

        // registered == false - Check if we aren't already connected
        if(registered==false && !connect(host, port)){                                         //Check connection
            std::cerr<<"Could not connect to server" << std::endl;
        }
        else {                                                           //If connection is good - GO!!!
            first_login = true;                                           //to not mess up the connection to the server - only if true, we read from socket
            registered = true;
            logout = false;                                                // thread will start to run - global variable
            oldUser=inputBySpace[2];                                      //olduser = this username that was entered - will be used when connected
                    //user->setName(inputBySpace[2]); //move this set name to after receiving "connected"
            std::stringstream ss;
            ss << "CONNECT\n" <<
            "accept-version:1.2\n" <<
            "host:stomp.cs.bgu.ac.il\n" <<
            "login:"+inputBySpace[2]+"\n" <<
            "passcode:"+inputBySpace[3]+"\n\n^@";                            // [3] is the password
            std::string frame = ss.str();
            sendFrame(frame); //ENCODER
        }

    ///------------------------Join send----------------------------------------------------
    }else if(first_word == "join"){
        string topic = inputBySpace[1];                                     // [1] is the topic name
        int topicId = user->subTopic(topic);
        if(topicId!=-1) {
            int receiptId = user->addReceiptId("join " + topic);          //The user subscribe to topic

            std::stringstream ss2;
            ss2 << "SUBSCRIBE\n" <<
                "destination:" + topic + "\n" <<
                "id:" + std::to_string(topicId) + "\n" <<
                "receipt:" + std::to_string(receiptId) + "\n\n^@";
            std::string frame = ss2.str();
            sendFrame(frame); //ENCODER
        }

    ///------------------------Exit send----------------------------------------------------
    }else if(first_word == "exit"){
        string topic = inputBySpace[1];                                     // [1] is the topic name
        int topicId = user->unsubtopic(topic);                            // changing the database of the topic
        if(topicId != -1){
            int receiptId = user->addReceiptId("exit "+topic);

            std::stringstream ss2;
            ss2 << "UNSUBSCRIBE\n" <<
                "id:"+std::to_string(topicId)+"\n" <<
                "receipt:"+std::to_string(receiptId)+"\n^@";
            std::string frame = ss2.str();
            sendFrame(frame); //ENCODER
        }


    ///------------------------Add send----------------------------------------------------
    }else if(first_word == "add"){
        string bookname = inputBySpace[2];
        for (int i=3; i<inputBySpace.size();i++)
            bookname += " "+inputBySpace[i];
        bool alreadyExists=false;
        for(Book* b : user->getInventory()){
            if(b->getBookname()==bookname){
                alreadyExists=true;
                break;
            }
        }
        if(!alreadyExists) {
            Book *new_book = new Book(bookname, inputBySpace[1],
                                      user->getName()); //creating new book with no loners - default is username
            user->addBook(new_book);

            std::stringstream ss;
            ss << "SEND\n" <<
               "destination:" + inputBySpace[1] + "\n\n" <<                              // [1] is the topic name
               user->getName() + " has added the book " + bookname + "\n^@";    // [2] is the book name
            std::string frame = ss.str();
            sendFrame(frame); //ENCODER
        }
        else{
            cout<<"Already have that book\n";
        }

     ///------------------------Borrow send----------------------------------------------------
    }else if(first_word == "borrow"){
        string bookname = inputBySpace[2];
        for (int i=3; i<inputBySpace.size();i++)
            bookname += " "+inputBySpace[i];
        user->addAskedBook(bookname,inputBySpace[1]);                   // [1] is the topic name

        std::stringstream ss;
        ss << "SEND\n" <<
            "destination:"+inputBySpace[1]+"\n\n" <<                            // [1] is the topic name
            user->getName()+" wish to borrow "+bookname+"\n^@";        // [2] is the book name
        std::string frame = ss.str();
        sendFrame(frame); //ENCODER

    ///------------------------Return send----------------------------------------------------
    }else if(first_word == "return"){
        string bookname = inputBySpace[2];
        for (int i=3; i<inputBySpace.size();i++)
            bookname += " "+inputBySpace[i];

        string loner="";
        for(Book* book: user->getInventory()){                  // searching for the book we want to return
            if(book->getBookname() == bookname) {               // [2] is the book name
                loner = book->getLoner();                       // if loner is real name, than we will delete the book and send the frame
                if(loner!=user->getName()) {                    // loner is the user, only if its not loaned
                    user->getInventory().erase(
                            std::remove(user->getInventory().begin(), user->getInventory().end(), book));
                    delete book;

                    std::stringstream ss;
                    ss << "SEND\n" <<
                       "destination:" + inputBySpace[1] + "\n\n" <<
                       "Returning " + bookname + " to " + loner + "\n^@";
                    std::string frame = ss.str();
                    sendFrame(frame); //ENCODER
                }
                break;
            }
        }

    ///------------------------Status send----------------------------------------------------
    }else if(first_word == "status"){
        std::stringstream ss;
        ss << "SEND\n" <<
           "destination:"+inputBySpace[1]+"\n\n" <<             // [1] is the topic name
           "book status\n^@";
        std::string frame = ss.str();
        sendFrame(frame); //ENCODER

     ///------------------------Logout send----------------------------------------------------
    }else if(first_word == "logout") {
        int receiptId = user->addReceiptId("logout");

        std::stringstream ss;
        ss << "DISCONNECT\n" <<
           "receipt:" + std::to_string(receiptId) + "\n^@";
        std::string frame = ss.str();
        sendFrame(frame); //ENCODER
    }

//------------------- end edit 11/1 --------------------------
}



// stompReceivedProcess
void ConnectionHandler::stompReceivedProcess(std::string &income) {
    //------------------- start edit 11/1 ------------------------
    std::vector<string> inputByLine;
    std::string delimiter = "\n";

    //Parsing the string
    size_t pos = 0;
    std::string token;
    while ((pos = income.find(delimiter)) != std::string::npos) {
        token = income.substr(0, pos);
        inputByLine.push_back(token);
        income.erase(0, pos + delimiter.length());
    }
    inputByLine.push_back(income);
    std::string first_word = inputByLine[0];

    ///-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.CONNECTED received-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    if (first_word == "CONNECTED") {
        user->setName(oldUser);                         // [2] is the user name
        std::cout << "Login successful\n";

        ///-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.RECEIPT received-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    } else if (first_word == "RECEIPT") {
        size_t pos = inputByLine[1].find(":");
        string receiptId_str = inputByLine[1].substr(pos + 1);
        string msg_receipt = user->receiptStatus(stoi(receiptId_str));
        //Check if this receipt is for join command
        if (msg_receipt.find("join") != std::string::npos) {
            pos = msg_receipt.find(" ");
            std::cout << "Joined club " + msg_receipt.substr(pos + 1) + "\n";
        }
            //Check if this receipt is for unsubscribe command
        else if (msg_receipt.find("exit") != std::string::npos) {
            pos = msg_receipt.find(" ");
            std::cout << "Exited club " + msg_receipt.substr(pos + 1) + "\n";
        }
            //Check if this receipt is for logout command
        else if (msg_receipt == "logout"){
            std::cout <<"Logged out...\n";
            this->logoutProcess();
        }

        ///-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.MESSAGE received-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    } else if (first_word == "MESSAGE") {

            ///---------------------User has added the book receive-----------  // Print that some user added a book
        if (inputByLine[5].find("has added the book") != std::string::npos){
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}
        }

            ///---------------------Wish to Borrow receive-----------  // if you have the book, tell the server
        else if (inputByLine[5].find("borrow") != std::string::npos) {
            pos = inputByLine[5].find(" ");
            string borrower = inputByLine[5].substr(0, pos);
            string bookname = inputByLine[5].substr(pos + 16);            //Do a substring from the end of word "borrow" until the end = book name
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}

            if (user->getName() != borrower) {
                for (Book *book: user->getInventory()) {
                    if (book->getBookname() == bookname & book->getInMyInventory()) {

                        std::stringstream ss;
                        ss << "SEND\n" <<
                           "destination:" + topic + "\n\n" <<
                           user->getName() + " has " + bookname <<
                           "\n^@";
                        std::string frame = ss.str();
                        sendFrame(frame); //ENCODER                            //Sending that the user has the book
                        break;
                    }
                }
            }
        }

            ///---------------------User has Book receive-------------  // if you wanted the book, take it
        else if (inputByLine[5].find("has") != std::string::npos) {
            pos = inputByLine[5].find(" ");
            string loner = inputByLine[5].substr(0, pos );
            string bookname = inputByLine[5].substr(pos + 5);
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}

            if (user->getName() != loner && user->wasAskedForBook(bookname)) {    // if i'm not the loner, AND i was the one who asked for it
                /** Assumption: only 1 user asked for this specific book...**/
                user->removeAskedBook(bookname);          // removes the book from the asked list
                Book *book = new Book(bookname, topic, loner);
                user->addBook(book);                      // added the book to user's inventory

                std::stringstream ss;
                ss << "SEND\n" <<
                   "destination:" + topic + "\n\n" <<
                   "Taking " + bookname + " from " + loner <<
                   "\n^@";
                std::string frame = ss.str();
                sendFrame(frame); //ENCODER                              //Sending that the user has the book
            }
        }

            ///---------------------Taking Book from Loner------------  // if loner, delete the book
        else if (inputByLine[5].find("Taking") != std::string::npos) {
            pos = inputByLine[5].find(" ");
            string msg = inputByLine[5].substr(pos + 1);    //Do a substring from the end of word "returning" until the end
            pos = msg.find_last_of(" ");
            string loner = msg.substr(pos + 1);
            string bookname = msg.substr(0, pos - 5);
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}

            if (user->getName() == loner) {
                for (Book *book : user->getInventory()) {
                    if (book->getBookname() == bookname) {
                        book->setInMyInventory(false);      // making the book to FALSE - the book won't be mine
                        break;
                    }
                }
            }
        }

             ///---------------------Return book to user---------------  // if you are the loner, than add the book
        else if (inputByLine[5].find("Returning") != std::string::npos) {
            pos = inputByLine[5].find(" ");
            string msg = inputByLine[5].substr(
                    pos + 1);    //Do a substring from the end of word "returning" until the end
            pos = msg.find_last_of(" ");
            string loner = msg.substr(pos + 1);
            string bookname = msg.substr(0, pos - 3);
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}

            if (user->getName() == loner) {
                bool bookGotDeleted = true;
                for (Book *book: user->getInventory()) {
                    if (book->getBookname() == bookname) {
                        book->setInMyInventory(true);       // making the book TRUE - I have the book now
                        bookGotDeleted = false;                   // when the user is logged out the book is gone. we might not have it
                        break;
                    }
                }
                if (bookGotDeleted) {                               // user logged out - we must create the book again
                    /** Assumption: the if this loner has to return it to someone else, it won't happen - he stole the book**/
                    std::string topic = inputByLine[3].substr(pos + 1);
                    Book *b = new Book(bookname, topic, user->getName());           // creating the new book
                    user->addBook(b);                                             // adding the book to the user
                }
            }
        }

            ///---------------------Status--------------------
        else if (inputByLine[5].find(("status")) != std::string::npos) {      // [5] is the details of the message
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::string booksList;
            for (Book *book: user->getInventory()) {
                if (book->getTopic() == topic & book->getInMyInventory())       //the book is in this genre and in my inventory
                    booksList = booksList + book->getBookname() + ",";
            }
            booksList = booksList.substr(0, booksList.length() - 1);    //To delete the last ","
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}

            std::stringstream ss;
            ss << "SEND\n" <<
               "destination:" + topic + "\n\n" <<
               user->getName() + ":" + booksList <<
               "\n^@";
            std::string frame = ss.str();
            sendFrame(frame); //ENCODER                             //Sending the user's book list of this topic
        }

            ///---------------------User: book,book...-----------  // Answer to book status
        else if (inputByLine[5].find(":") != std::string::npos) {
            pos = inputByLine[3].find(":");        // [3] in destination topic
            std::string topic = inputByLine[3].substr(pos + 1);
            std::cout<< topic+": "+inputByLine[5]+"\n";                 //Printing to the screen {topic}:{content}
        }

    ///-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.ERROR received-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    } else if (first_word == "ERROR") {
        ///---------------------User already logged in------------
        if (inputByLine[2].find("already logged") != std::string::npos) {
            std::cout << "User already logged in\n";
        }

        ///---------------------Wrong password------------
        else if (inputByLine[2].find("password") != std::string::npos) {
            std::cout << "Wrong Password\n";
            this->logoutProcess();
        }

        ///---------------------Logged in with another User------------
        else if (inputByLine[2].find("logged in with another") != std::string::npos) {
            std::cout << "Another user is already logged in\n";
            this->logoutProcess();
        }
    }
    //------------------- end edit 14/1 --------------------------
}

void ConnectionHandler::logoutProcess (){ // CHECK CHECK CHECK CHECK
    //------------------- start edit 12/1 ------------------------
    registered=false;
    delete user;
    user= new User();           //Removing all the parameters of the user
    logout = true;              //Global variable
    this->close();              //Closing the socket
    //------------------- end edit 11/1 --------------------------
}













