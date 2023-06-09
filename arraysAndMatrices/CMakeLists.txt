cmake_minimum_required(VERSION 3.25)
project(linkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(linkedList main.c)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/acadele.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

