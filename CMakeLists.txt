cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

link_libraries("-lboost_system")

add_executable(Boost_Echo_Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        makefile src/Stomp/stopmClient.cpp include/stopmClient.h src/Stomp/keyboardInputSend.cpp include/keyboardInputSend.h src/Stomp/socketReader.cpp include/socketReader.h src/Stomp/stompConnectionHandler.cpp include/stompConnectionHandler.h src/Stomp/user.cpp src/Stomp/user.h src/Stomp/Book.cpp include/Book.h)
