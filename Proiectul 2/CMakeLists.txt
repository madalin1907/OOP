cmake_minimum_required(VERSION 3.21)
project(Proiectul_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(util)

add_executable(Proiectul_2
        util/functions.cpp
        util/functions.h
        util/IoBase.cpp
        util/IoBase.h
        143_Florea_Madalin.cpp)
