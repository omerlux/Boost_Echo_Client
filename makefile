CFLAGS: = -c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS: = -lboost_system

all: StompBookClubClient
    g++ -pthread -o bin/StompBookClubClient bin/ConnectionHandler.o  bin/Book.o bin/keyboardInputSend.o bin/socketReader.o bin/User.o $(LDFLAGS)

StompBookClubClient: bin/StompBookClubClient bin/ConnectionHandler.o  bin/Book.o bin/keyboardInputSend.o bin/socketReader.o bin/User.o

bin/Book.o: src/Stomp/Book.cpp
    g++ -pthread $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/ConnectionHandler.o: src/Stomp/ConnectionHandler.cpp
    g++ -pthread $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/keyboardInputSend.o: src/Stomp/keyboardInputSend.cpp
    g++ -pthread $(CFLAGS) -o bin/keyboardInputSend.o src/keyboardInputSend.cpp

bin/socketReader.o: src/Stomp/socketReader.cpp
    g++ -pthread $(CFLAGS) -o bin/socketReader.o src/socketReader.cpp

bin/StompBookClubClient.o: src/Stomp/StompBookClubClient.cpp
    g++ -pthread $(CFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

bin/User.o: src/Stomp/User.cpp
    g++ -pthread $(CFLAGS) -o bin/User.o src/User.cpp

.PHONY: clean
clean:
    rm -f bin/*