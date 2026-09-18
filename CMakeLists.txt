cmake_minimum_required(VERSION 3.10)
project(csopesy_mo3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(csopesy_mo3
    src/main.cpp
    src/helpers.cpp
)
