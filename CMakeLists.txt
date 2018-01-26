cmake_minimum_required(VERSION 3.9)
project(esb)

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{BOOST})

link_directories($ENV{BOOST}/stage/lib)

add_executable(esb main.cpp)