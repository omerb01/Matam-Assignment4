cmake_minimum_required(VERSION 3.9)
project(Assignment4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

add_executable(Assignment4 Group.h exceptions.h Group.cpp
        Clan.cpp Clan_test.cpp #[[MtmSet.h Area.cpp Area.h Area_test.cpp]])