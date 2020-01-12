# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib

# All Targets
all: stompClient

# Tool invocations
stompClient: bin/Stomp/stompClient.o bin/Stomp/Book.o bin/Stomp/keyboardInputSend.o bin/Stomp/socketReader.o bin/Stomp/stompConnectionHandler.o bin/Stomp/User.o bin/connectionHandler.o bin/echoClient.o 
	@echo 'Building target: stompClient'
	@echo 'Invoking: C++ Linker'
	@echo 'Finished building target: stompClient'
	@echo ' '

# Depends on the source and header files
bin/Stomp/stompClient.o: bin/Stomp/stompClient.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/stompClient.o bin/Stomp/stompClient.cpp
bin/Stomp/Book.o: bin/Stomp/Book.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/Book.o bin/Stomp/Book.cpp
bin/Stomp/keyboardInputSend.o: bin/Stomp/keyboardInputSend.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/keyboardInputSend.o bin/Stomp/keyboardInputSend.cpp
bin/Stomp/socketReader.o: bin/Stomp/socketReader.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/socketReader.o bin/Stomp/socketReader.cpp
bin/Stomp/stompConnectionHandler.o: bin/Stomp/stompConnectionHandler.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/stompConnectionHandler.o bin/Stomp/stompConnectionHandler.cpp
bin/Stomp/User.o: bin/Stomp/User.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Stomp/User.o bin/Stomp/User.cpp
bin/connectionHandler.o: bin/connectionHandler.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/connectionHandler.o bin/connectionHandler.cpp
bin/echoClient.o: bin/echoClient.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/echoClient.o bin/echoClient.cpp

#Clean the build directory
clean: 
	rm -f bin/*
