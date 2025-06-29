cmake_minimum_required(VERSION 3.0)
project(calculation)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculater 
    main.cpp 
    calculate.cpp 
    utils.cpp
)