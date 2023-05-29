cmake_minimum_required(VERSION 3.24)
project(aleas_de_la_destinee)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(aleas_de_la_destinee
        include/player.h
        include/story.h
        main.cpp
        player.cpp proba.cpp include/rooms.h)
