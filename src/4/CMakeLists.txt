


include_directories(./ ../../include)

cmake_minimum_required(VERSION 3.14)
project(4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(run main.cpp)