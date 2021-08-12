cmake_minimum_required(VERSION 3.19)
project(db_runtime C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(
        db_runtime
        STATIC

        src/ints.c
        src/ints.cpp
        src/cfile.cpp)
target_include_directories(db_runtime PUBLIC Include)