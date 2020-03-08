cmake_minimum_required(VERSION 3.14)
project(9 CXX)

set(SOURCE_DIR ${9_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
file(GLOB SRCs src/*.cc)
add_executable(9 ${SRCs} main.cc)