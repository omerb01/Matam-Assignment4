cmake_minimum_required(VERSION 3.9)
project(Assignment4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

add_executable(Assignment4 exceptions.h
        testMacros.h MtmSet.h Group.h Clan.h Area.h Area.cpp
        Clan.cpp Group.cpp #[[Plain.cpp Plain.h]] Mountain.h Mountain.cpp Mountain_test.cpp)