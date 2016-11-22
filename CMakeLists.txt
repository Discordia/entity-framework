cmake_minimum_required(VERSION 3.6)
project(entity_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fmax-errors=1 -Wall")

file(GLOB SOURCE_FILES
        test/*
        src/*)

add_executable(entityframework ${SOURCE_FILES})