cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

link_libraries("-lboost_system")

add_executable(StompBookClubClient
        makefile src/Stomp/StompBookClubClient.cpp include/StompBookClubClient.h src/Stomp/ConnectionHandler.cpp include/ConnectionHandler.h src/Stomp/User.cpp include/User.h src/Stomp/Book.cpp include/Book.h src/Stomp/socketReader.cpp include/socketReader.h src/Stomp/keyboardInputSend.cpp include/keyboardInputSend.h)
