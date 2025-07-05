cmake_minimum_required(VERSION 3.10)

project(calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(calculator 
    main.cpp 
    calculate.cpp 
    utils.cpp
    # tcp_server.cpp
)

set(HEADERS
    calculate.h
    utils.h
    # tcp_server.h
)
