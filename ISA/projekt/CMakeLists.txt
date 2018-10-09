cmake_minimum_required(VERSION 3.8)
project(projekt)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c arguments.c)
add_executable(projekt ${SOURCE_FILES})