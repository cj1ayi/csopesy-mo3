cmake_minimum_required(VERSION 3.10)
project(csopesy_mo3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(csopesy_mo3
    src/main.cpp
    src/helpers.cpp
    src/marquee.cpp
    src/commands.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(csopesy_mo3 PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(csopesy_mo3 PRIVATE /W4 /WX)
else()
    target_compile_options(csopesy_mo3 PRIVATE -Wall -Wextra -Werror)
endif()
