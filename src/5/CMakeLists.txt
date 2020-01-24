cmake_minimum_required(VERSION 3.14)
project(5 CXX)

set(SOURCE_DIR ${5_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB SRCs src/*.cc)
add_subdirectory(test)
add_executable(5 ${SRCs} main.cc)