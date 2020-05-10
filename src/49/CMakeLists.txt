

cmake_minimum_required(VERSION 3.14)
project(49 CXX)

set(SOURCE_DIR ${49_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(49 main.cc)