# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11 -Include -pthread
LDFLAGS = -lboost_system -pthread
LFLAGS  = -L/usr/lib

# All Targets
all: StompBookClubClient

# Tool invocations
StompBookClubClient: bin/Stomp/StompBookClubClient.o bin/Stomp/Book.o bin/Stomp/keyboardInputSend.o bin/Stomp/socketReader.o bin/Stomp/ConnectionHandler.o bin/Stomp/User.o $(LDFLAGS)
	@echo 'Building target: StompBookClubClient'
	@echo 'Invoking: C++ Linker'
	@echo 'Finished building target: stompClient'
	@echo ' '

# Depends on the source and header files
bin/Stomp/stompClient.o: bin/Stomp/stompClient.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/StompBookClubClient.o bin/Stomp/StompBookClubClient.cpp -pthread
bin/Stomp/Book.o: bin/Stomp/Book.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/Book.o bin/Stomp/Book.cpp
bin/Stomp/keyboardInputSend.o: bin/Stomp/keyboardInputSend.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/keyboardInputSend.o bin/Stomp/keyboardInputSend.cpp
bin/Stomp/socketReader.o: bin/Stomp/socketReader.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/socketReader.o bin/Stomp/socketReader.cpp
bin/Stomp/stompConnectionHandler.o: bin/Stomp/stompConnectionHandler.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/stompConnectionHandler.o bin/Stomp/stompConnectionHandler.cpp
bin/Stomp/User.o: bin/Stomp/User.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Stomp/User.o bin/Stomp/User.cpp

#Clean the build directory
clean: 
	rm -f bin/*
