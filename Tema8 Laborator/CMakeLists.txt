cmake_minimum_required(VERSION 3.21)

project(POO)
set(CMAKE_CXX_STANDARD 17)

set(UTIL_SOURCE_FILES util/IoBase.h util/IoBase.cpp util/functions.h util/functions.cpp)

add_executable(main1 main1.cpp ${UTIL_SOURCE_FILES})
add_executable(main2 main2.cpp ${UTIL_SOURCE_FILES})
add_executable(main3 main3.cpp ${UTIL_SOURCE_FILES})
add_executable(main4 main4.cpp ${UTIL_SOURCE_FILES})
