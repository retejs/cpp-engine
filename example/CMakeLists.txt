cmake_minimum_required(VERSION 3.0)

project(example)
SET(CMAKE_BUILD_TYPE Debug)

if(EMSCRIPTEN)
    SET(CMAKE_C_COMPILER emcc)
    SET(CMAKE_CXX_COMPILER em++)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 --std=c++11")
elseif(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11")
endif()


include_directories("../src")
add_executable(example main.cpp)