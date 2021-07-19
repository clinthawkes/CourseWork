cmake_minimum_required(VERSION 3.14)
project(heron C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -lm")

add_executable(heron main.c)