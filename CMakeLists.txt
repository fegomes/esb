cmake_minimum_required(VERSION 3.9)
project(esb)

set(CMAKE_CXX_STANDARD 14)

file(MAKE_DIRECTORY bin)

add_subdirectory(log)
add_subdirectory(http)
add_subdirectory(listener)