cmake_minimum_required(VERSION 3.23)
project(c8552a1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(c8552a1
        CMultiThread.cpp
        CMultiThread.h
        Semaphore.h
        main.cpp)
